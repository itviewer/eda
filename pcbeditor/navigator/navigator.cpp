#include "navigator.h"

#include "pcbscene.h"

Navigator::Navigator(QWidget *parent)
    :QTreeWidget(parent)
{
    resize(150,0);
    setHeaderHidden(true);
}

Navigator::~Navigator()
{

}

QSize Navigator::sizeHint() const
{
    return size();
}

void Navigator::createNavigator()
{
}
