#include "tp_qt_control_widgets/ToolBar.h"
#include "tp_control/CoreInterface.h"

#include <QSignalMapper>
#include <QList>
#include <QAction>

namespace tp_qt_control_widgets
{

namespace
{
struct ButtonDetails_lt
{
  QAction* action{nullptr};
  tp_utils::StringID value;
};
}

//##################################################################################################
struct ToolBar::Private
{
  Q* q;

  tp_control::CoreInterface* coreInterface;
  tp_control::CoreInterfaceHandle channel;

  QList<ButtonDetails_lt> buttons;

  //################################################################################################
  Private(Q* q_, tp_control::CoreInterface* coreInterface_, tp_control::CoreInterfaceHandle channel_):
    q(q_),
    coreInterface(coreInterface_),
    channel(std::move(channel_))
  {

  }
};

//##################################################################################################
ToolBar::ToolBar(tp_control::CoreInterface* coreInterface, const tp_control::CoreInterfaceHandle& channel, QWidget* parent):
  QToolBar(parent),
  d(new Private(this, coreInterface, channel))
{

}

//##################################################################################################
ToolBar::~ToolBar()
{
  delete d;
}

//##################################################################################################
void ToolBar::addButton(const QString& icon, const QString& toolTip, const tp_utils::StringID& value)
{
  TP_UNUSED(icon);
  TP_UNUSED(toolTip);

  ButtonDetails_lt details;
  details.value = value;
  details.action->setCheckable(true);

  d->buttons.append(details);
}

//##################################################################################################
void ToolBar::buttonClicked(int index)
{
  TP_UNUSED(index);
}


}
