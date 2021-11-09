/**
 * @file GraphicsBlock.h
 * @author Tomáš Lisický (xlisic01)
 * @brief Hlavička grafickej reprezentácie bloku.
 * @date 2021-05-06
 */
#ifndef GRAPHICSBLOCK_H
#define GRAPHICSBLOCK_H

#include "block_schema.h"
#include "pin.h"

#include <QGraphicsItem>
#include <QPainter>

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

/**
 * @brief The GraphicsBlock class - trieda grafického bloku
 */
class GraphicsBlock : public QGraphicsItem {
    public:
        /**
         * @brief GraphicsBlock
         * @param arg_schema - schéma, do ktorej sa zapisujú bloky pre simuláciu
         * @param arg_type - typ bloku pre schému a výpočet
         * @param parent - rodič (deštruktor, dedenie a pod.)
         */
        GraphicsBlock(Block_schema *arg_schema, Block_type arg_type, QGraphicsItem *parent = nullptr);

        std::string var_block_name;

    private:
        Block_schema *obj_schema;

        Pin *input0;
        Pin *input1;
        Pin *output0;

        QBrush m_brush;

        /**
         * @brief hoverEnterEvent - sníma pohyb myši po pinoch, ktoré následne prefarbí
         */
        void hoverEnterEvent(QGraphicsSceneHoverEvent *);

        /**
         * @brief hoverLeaveEvent - sníma odchod myši, piny prefarbí naspäť
         */
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

    protected:
        /**
         * @brief boundingRect - vymedzí hranice plochy bloku
         * @return - vymedzená plocha
         */
        QRectF boundingRect() const;

        /**
         * @brief paint - vykreslí blok na vymedzenú plochu
         * @param painter - vykresľovač
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

        /**
         * @brief Zmeni meno bloku
         */
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSBLOCK_H
