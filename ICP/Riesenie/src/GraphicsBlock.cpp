/**
 * @file GraphicsBlock.cpp
 * @author Tomáš Lisický (xlisic01)
 * @brief Graficka reprezentácia bloku.
 * @date 2021-05-06
 */

#include "GraphicsBlock.h"
#include <QInputDialog>

GraphicsBlock::GraphicsBlock(Block_schema *arg_schema, Block_type arg_type, QGraphicsItem *parent) : QGraphicsItem(parent), m_brush(Qt::gray) {
    obj_schema = arg_schema;
    var_block_name = obj_schema->add_block(arg_type);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    setAcceptHoverEvents(true);

    QPen local_pen;
    local_pen.setWidth(3);
    local_pen.setColor(Qt::darkGreen);

    if(arg_type == sum || arg_type == sub){
        input0 = new Pin(obj_schema,0,false,this);
        input1 = new Pin(obj_schema,1,false,this);
        output0 = new Pin(obj_schema,0,true,this);

        input0->setPos(1,30);
        input1->setPos(1,60);
        output0->setPos(60,45);
    }
    else{
        input0 = new Pin(obj_schema,0,false,this);
        output0 = new Pin(obj_schema,0,true,this);

        input0->setPos(1,45);
        output0->setPos(60,45);
    }
}

QRectF GraphicsBlock::boundingRect() const {
    return QRectF(0,0,70,100);
}

void GraphicsBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QPen saved_pen = painter->pen();
    QPen local_pen;
    local_pen.setWidth(5);
    painter->setPen(local_pen);
    painter->setBrush(m_brush);

    painter->drawRect(6,6,59,90);
    painter->drawText(QPointF(25,55), QString::fromStdString(obj_schema->get_block_label(var_block_name) ) );

    painter->setPen(saved_pen);
}

void GraphicsBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    m_brush = Qt::darkGray;
    update();
}

void GraphicsBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    m_brush = Qt::gray;
    update();
}

void GraphicsBlock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    (void)event; //warning
    bool ok;
    QString text = QInputDialog::getText(nullptr, "Change block name",
                                         "Block name:", QLineEdit::Normal,
                                         QString::fromStdString(var_block_name) , &ok);
    std::string new_name = text.toStdString();
    if (ok && !text.isEmpty()){
        if(obj_schema->change_block_name(var_block_name, new_name) == 0){
            var_block_name = new_name;
        }
    }
}


