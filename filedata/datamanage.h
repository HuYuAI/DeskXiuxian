#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFileInfo>
#include <QDebug>
#include <QDate>
#include <QSqlQuery>
#include <QMutex>
#include <QJsonObject>
#include "public/public_macro.h"

/**
 * @brief 文件管理类
 */
class DataManage : public QObject
{
public:

    /**
     * @brief 获取单例
     */
    static DataManage* GetInstance();

    /**
     * @brief 获取表单中对应的列数据
     * @return 查询不到则返回空，否则返回查询值
     */
    QString GetTableToInfo(QString table_name, QString column_name);

    /**
     * @brief 获取上次游戏时间
     */
    QString GetLastGameTime();

    /**
     * @brief 关闭数据库
     */
    void DatabaseClose();

    /**
     * @brief 写入游戏最后运行时间
     */
    void SetGameLastPlayTime();

    ~DataManage();

public slots:

    /**
     * @brief 保存角色基本信息数据 槽函数
     */
    void SlotSaveRoleInfoToDatabase(QJsonObject role_data);

    /**
     * @brief 保存角色物品数据 槽函数
     */
    void SlotSaveRoleItemToDatabase(QJsonObject role_item_data);

    /**
     * @brief 保存角色相关属性系数数据 槽函数
     */
    void SlotSaveRoleCoefficientToDatabase(QJsonObject RC_data);

private:
    DataManage();
    // 阻止拷贝构造函数和赋值运算符
    DataManage(const DataManage&) = delete;
    DataManage& operator=(const DataManage&) = delete;
    static QMutex mutex;  // 互斥锁
    static DataManage* instance;  // 单例对象指针

    /**
     * @brief 打开数据库
     */
    void OpenDatabase(QString path);

    void OpenDatabase(QString host, int port, QString username, QString password, QString databaseName);

    /**
     * @brief 创建数据库
     */
    void CreateDatabase(QString path);

    /**
     * @brief 检查数据库
     */
    bool CheckTablesExist();

    /**
     * @brief 配置文件读取
     */
    QSettings *file_setting_;

    /**
     * @brief 数据库操作
     */
    QSqlDatabase database_;

};

#endif // DATAMANAGE_H
