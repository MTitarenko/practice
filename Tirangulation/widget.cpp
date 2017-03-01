#include "widget.h"
#include "ui_widget.h"
#include "time.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    srand (time(0));
    ui->setupUi(this);

   scene = new GraphicsScene;
   scene->setSceneRect(0, 0, ui->graphicsView->width() - 20,
                       ui->graphicsView->height() - 20);
   ui->radioButton->setChecked(true);

   connect(ui->pushButton, &QPushButton::clicked, scene, &GraphicsScene::slotStart);
   connect(ui->pushButton_2, &QPushButton::clicked, scene, &GraphicsScene::slotLookFor);
   connect(ui->pushButton_3, &QPushButton::clicked, scene, &GraphicsScene::slotRandomPoints);
   connect(ui->radioButton, &QRadioButton::clicked, scene, &GraphicsScene::slotVertices);
   connect(ui->radioButton_2, &QRadioButton::clicked, scene, &GraphicsScene::slotPointLookFor);

   ui->graphicsView->setRenderHint(QPainter::Antialiasing);
   ui->graphicsView->setScene(scene);
   ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Widget::~Widget()
{
    delete ui;
    delete scene;
}
