/**
 * @file mainwindow.h
 * @author Tomáš Lisický (xlisic01)
 * @brief Hlavička hlavného okna aplikacie.
 * @date 2021-05-06
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "block_schema.h"
#include "GraphicsBlock.h"

#include <iostream>
#include <fstream>

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFileDialog>
#include <QMouseEvent>

#include <qmath.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        /**
         * @brief MainWindow - vytvorí hlavné okno aplikácie, kde sa vyho
         * @param parent
         */
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        /**
         * @brief on_pushButton_4_pressed - po stlačení tlačítka vykreslí blok "+"
         */
        void on_pushButton_4_pressed();

        /**
         * @brief on_pushButton_5_pressed - po stlačení tlačítka vykreslí blok "-"
         */
        void on_pushButton_5_pressed();

        /**
         * @brief on_pushButton_6_pressed - po stlačení tlačítka vykreslí blok "++"
         */
        void on_pushButton_6_pressed();

        /**
         * @brief on_pushButton_7_pressed - po stlačení tlačítka vykreslí blok "--"
         */
        void on_pushButton_7_pressed();

        /**
         * @brief on_pushButton_8_clicked - otvorí dialógové okno, s výberom, kam uložiť C++ reprezentáciu schémy
         */
        void on_pushButton_8_clicked();

    private:
        Ui::MainWindow *ui;
        QGraphicsScene *obj_scene;
        Block_schema *obj_block_schema;
        QFileDialog *file_dialog;
        QPen var_default_pen;

        QPointF var_mouse_scene_position, var_mouse_viewport_position;
        QPointF var_line_start_position, var_line_end_position;

        /**
         * @brief ViewZoom - približuje / vzdiaľuje
         * @param param_view - pohľad, ktorý sa bude približ. / vzdiaľ.
         * @param param_factor - faktor približ. / vzdiaľ.
         */
        void ViewZoom(QGraphicsView* param_view, double param_factor);

        /**
         * @brief eventFilter - sleduje pohyby myši a jej kolečka na pohľade
         * @param param_object - nepoužitý
         * @param param_event - informácia, o akú udalosť sa jedná
         * @return
         */
        bool eventFilter(QObject *param_object, QEvent *param_event);
};
#endif // MAINWINDOW_H
