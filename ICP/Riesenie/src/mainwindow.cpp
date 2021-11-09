/**
 * @file mainwindow.cpp
 * @author Tomáš Lisický (xlisic01)
 * @brief Hlavné okno aplikácie.
 * @date 2021-05-06
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    obj_block_schema = new Block_schema();

    file_dialog = new QFileDialog(this); // vytvori okno na vyber suboru

    var_default_pen.setWidth(3);

    obj_scene = new QGraphicsScene(this); // vytvorenie scény (plátna)
    ui->graphicsView->setScene(obj_scene); // určenie plátna na vykreslenie
    ui->graphicsView->viewport()->installEventFilter(this); // zachytávanie udalostí
    ui->graphicsView->setMouseTracking(true); // sledovanie myši

    // vykreslenie stredovej osi
    obj_scene->addLine(-5,0,5,0);
    obj_scene->addLine(0,-5,0,5);
}

MainWindow::~MainWindow() {
    delete ui;
    delete obj_block_schema;
}

void MainWindow::ViewZoom(QGraphicsView* param_view, double param_factor) {
    param_view->scale(param_factor, param_factor);
    param_view->centerOn(var_mouse_scene_position);

    QPointF var_viewport_position_difference = var_mouse_viewport_position - QPointF(param_view->viewport()->width() / 2.0, param_view->viewport()->height() / 2.0);
    QPointF var_center = param_view->mapFromScene(var_mouse_scene_position) - var_viewport_position_difference;

    param_view->centerOn(param_view->mapToScene(var_center.toPoint()));
}

bool MainWindow::eventFilter(QObject *param_object, QEvent *param_event) {
    // sníma pohyb kolečkom na myši
    // ak je zároveň stisknutá kĺavesa CTRL, pohyb kolečkom môže približovať odďaľovať pohľad
    if (param_event->type() == QEvent::Wheel) {
        QWheelEvent* var_wheel_event = static_cast<QWheelEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        if (QApplication::keyboardModifiers() == Qt::ControlModifier) { // pozrie či bol stlačený Ctrl
            double var_angle = var_wheel_event->angleDelta().y();
            double var_factor = qPow(1.001, var_angle); // 1.001 je cistlivosť zoomovania
            ViewZoom(ui->graphicsView, var_factor);
            return true;
        }
    }
    // sníma pohyb myši a priebežne si ukladá jej pozíciu
    // využitie pre zoomovanie na pozíciu myši
    else if (param_event->type() == QEvent::MouseMove) {
        QMouseEvent* var_mouse_event = static_cast<QMouseEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        QPointF var_difference = var_mouse_viewport_position - var_mouse_event->pos();
        if (qAbs(var_difference.x()) > 10 || qAbs(var_difference.y()) > 10) { // ak sa myš vzdiali 10 pixelov od predošlej uloženej pozície...
            var_mouse_viewport_position = var_mouse_event->pos(); // uloží si obe jej pozície
            var_mouse_scene_position = ui->graphicsView->mapToScene(var_mouse_event->pos());
        }
    }
    Q_UNUSED(param_object)
    return false;
}

void MainWindow::on_pushButton_4_pressed() {
    GraphicsBlock *new_block = new GraphicsBlock(obj_block_schema, sum);
    obj_scene->addItem(new_block);
}

void MainWindow::on_pushButton_5_pressed() {
    GraphicsBlock *new_block = new GraphicsBlock(obj_block_schema, sub);
    obj_scene->addItem(new_block);
}

void MainWindow::on_pushButton_6_pressed() {
    GraphicsBlock *new_block = new GraphicsBlock(obj_block_schema, inc);
    obj_scene->addItem(new_block);
}

void MainWindow::on_pushButton_7_pressed() {
    GraphicsBlock *new_block = new GraphicsBlock(obj_block_schema, dec);
    obj_scene->addItem(new_block);
}

void MainWindow::on_pushButton_8_clicked() {
    QString var_file_name;

    file_dialog->setAcceptMode(QFileDialog::AcceptSave);
    if (file_dialog->exec()) {
        QStringList file_names = file_dialog->selectedFiles();
        if ( file_names.count() ) {
            var_file_name = file_names.at(0);
        }
    }

    if (!var_file_name.isEmpty()) {
        std::ofstream my_file(var_file_name.toStdString());
        my_file << obj_block_schema->generate_sim_code();
        my_file.close();
    }

}
