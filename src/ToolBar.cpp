#include "tdp_control_widgets/ToolBar.h"
#include "tp_control/CoreInterface.h"

#include <QSignalMapper>
#include <QList>
#include <QAction>

namespace tdp_control_widgets
{

namespace
{
struct ButtonDetails_lt
{
  QAction* action{nullptr};
  tp_utils::StringID value;
};
}

struct ToolBar::Private
{
  ToolBar* q;

  tp_control::CoreInterface* coreInterface;
  tp_control::CoreInterfaceHandle channel;

  QList<ButtonDetails_lt> buttons;
  QSignalMapper mapper;

  //################################################################################################
  Private(ToolBar* q_, tp_control::CoreInterface* coreInterface_, tp_control::CoreInterfaceHandle channel_):
    q(q_),
    coreInterface(coreInterface_),
    channel(std::move(channel_))
  {

  }

  ////################################################################################################
  //void updateButtons()
  //{
  //  tp_utils::StringID value = coreInterface->getChannelData(channel).value<tp_utils::StringID>();
  //
  //  Q_FOREACH(const ButtonDetails_lt& details, buttons)
  //    details.action->setChecked(details.value == value);
  //}
  //
  ////################################################################################################
  //static void channelChanged(const CoreInterfaceHandle& handle, void* opaque)
  //{
  //  auto* d = (Private*)opaque;
  //
  //  if(handle == d->channel)
  //    d->updateButtons();
  //}
};

//##################################################################################################
ToolBar::ToolBar(tp_control::CoreInterface* coreInterface, const tp_control::CoreInterfaceHandle& channel, QWidget* parent):
  QToolBar(parent),
  d(new Private(this, coreInterface, channel))
{
  //connect(&d->mapper, SIGNAL(mapped(int)), this, SLOT(buttonClicked(int)));
  //coreInterface->registerCallback(d->channelChanged, d);
}

//##################################################################################################
ToolBar::~ToolBar()
{
  delete d;
}

//##################################################################################################
void ToolBar::addButton(const QString& icon, const QString& toolTip, const tp_utils::StringID& value)
{
  ButtonDetails_lt details;
  details.value = value;
  details.action = addAction(QIcon(icon), toolTip, &d->mapper, SLOT(map()));
  details.action->setCheckable(true);
  d->mapper.setMapping(details.action, d->buttons.size());

  d->buttons.append(details);

  //d->updateButtons();
}

//##################################################################################################
void ToolBar::buttonClicked(int index)
{
  TP_UNUSED(index);
  //if(index>=0 && index<d->buttons.size())
  //  d->coreInterface->setChannelData(d->channel, QVariant::fromValue(d->buttons.at(index).value));

  //d->updateButtons();
}


}
