#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    // 初始化成员变量
    role_obj_->RoleSystem::GetInstance();
    logger_ = Logger::GetInstance();

    // 初始化UI设置
    // 设置logo
    setWindowIcon(QIcon(":/res/logo.jpg"));

    // 设置窗口标题
    setWindowTitle("桌面修仙");

    // 固定窗口
    setFixedSize(width(),height());

    // 将窗口居中显示
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()
                    )
                );

    //外层widget布局
    ui->centralwidget->setLayout(ui->outerLayout);

    //主角选项卡布局
    ui->role_page->setLayout(ui->role_Layout);
    ui->bisic_Att_Box->setLayout(ui->bisic_Layout);
    ui->equipment_Box->setLayout(ui->equipment_Layout);

    /////////////测试代码
    QTimer *timer = new QTimer;
    timer->setInterval(1000); // 设置定时器间隔为 1 秒
    timer->setSingleShot(false); // 设置定时器为非单次触发

    // 连接定时器的 timeout() 信号到槽函数
    QObject::connect(timer, &QTimer::timeout, this,&MainUI::SlotShowMsg);
    timer->start();

    // 创建日志记录器


    // 将日志记录器的 log() 槽连接到 Qt 的日志处理器
    QObject::connect(this, SIGNAL(SignalLogOut(QtMsgType, const QMessageLogContext&, const QString&)),
                     logger_, SLOT(SlotOutTolog(QtMsgType, const QMessageLogContext&, const QString&)));

}

MainUI::~MainUI()
{
    delete ui;
}

void MainUI::AddMessage(QString& msg)
{
    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm:ss");

    QString display_text = time_stamp + "：" + msg;

    ui->listWidget->addItem(display_text);
    // 滚动到底部
    // 延迟滚动到底部
    QTimer::singleShot(0, this, [this]() {
        QScrollBar* scrollbar = ui->listWidget->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
    });
    // 将消息记录到日志
    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
}

Ui::MainUI* MainUI::GetUI()
{
    return ui;
}

void MainUI::UpdateRoleInformation(QString name, QString life, QString prestige, QString cultivation)
{
    ui->role_name->setText(name);
    ui->role_life->setText(life);
    ui->role_prestige->setText(prestige);
    ui->role_cultivation->setText(cultivation);
}

void MainUI::UpdatePhysicalStrength(QString exp, QString agg, QString def, QString hp)
{
    ui->role_exp->setText(exp);
    ui->role_agg->setText(agg);
    ui->role_def->setText(def);
    ui->role_hp->setText(hp);
}

/**
 * @brief 更新角色装备,武器、法宝、头盔、上衣、腰带、鞋、首饰
 */
void MainUI::UpdateEquip(QString weapon, QString magic, QString helmet, QString clothing, QString britches, QString shoe, QString jewelrt)
{
    ui->equip_weapon->setText(weapon);
    ui->equip_magic->setText(magic);
    ui->equip_helmet->setText(helmet);
    ui->equip_clothing->setText(clothing);
    ui->equip_britches->setText(britches);
    ui->equip_shoe->setText(shoe);
    ui->equip_jewelry->setText(jewelrt);
}

void MainUI::SlotUpdateUI(RoleUI part, QString new_name)
{
    switch (part)
    {
        case kUnknown:
        break;
    case kRoleName:
        ui->role_name->setText(new_name);
        break;
    case kRoleLife:
        ui->role_life->setText(new_name);
        break;
    case kRolePrestige:
        ui->role_prestige->setText(new_name);
        break;
    case kRoleCultivation:
        ui->role_cultivation->setText(new_name);
        break;
    case kRoleExp:
        ui->role_exp->setText(new_name);
        break;
    case kRoleAgg:
        ui->role_agg->setText(new_name);
        break;
    case kRoleDef:
        ui->role_def->setText(new_name);
        break;
    case kRoleHp:
        ui->role_hp->setText(new_name);
        break;
    case kAttMetal:
    case kAttWood:
    case kAttWater:
    case kAttFire:
    case kAttEarth:
        break;
    case kEquipWeapon:
        ui->equip_weapon->setText(new_name);
        break;
    case kEquipMagic:
        ui->equip_magic->setText(new_name);
        break;
    case kEquipHelmet:
        ui->equip_helmet->setText(new_name);
        break;
    case kEquipClothing:
        ui->equip_clothing->setText(new_name);
        break;
    case kEquipBritches:
        ui->equip_britches->setText(new_name);
        break;
    case kEquipShoe:
        ui->equip_shoe->setText(new_name);
        break;
    case kEquipJewelrt:
        ui->equip_jewelry->setText(new_name);
        break;
    case kPropRenameCard:
        break;
    }
}

