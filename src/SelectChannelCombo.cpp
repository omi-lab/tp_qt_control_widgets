#include "tdp_control_widgets/SelectChannelCombo.h"
#include "tp_control/CoreInterface.h"

namespace tdp_control_widgets
{

//##################################################################################################
struct SelectChannelCombo::Private
{
  TP_NONCOPYABLE(Private);
  SelectChannelCombo* q;
  tp_control::CoreInterface* coreInterface;
  tp_utils::StringID typeID;

  tp_control::CoreInterfaceHandle selectedChannel;

  tp_control::ChannelListChangedCallback channelListChangedCallback;

  //################################################################################################
  Private(SelectChannelCombo* q_, tp_control::CoreInterface* coreInterface_, tp_utils::StringID typeID_):
    q(q_),
    coreInterface(coreInterface_),
    typeID(std::move(typeID_))
  {
    channelListChangedCallback = [&](){updateList();};
    coreInterface->registerCallback(&channelListChangedCallback);
    updateList();
  }

  //################################################################################################
  ~Private()
  {
    coreInterface->unregisterCallback(&channelListChangedCallback);
  }

  //##################################################################################################
  void updateList()
  {
    q->blockSignals(true);

    q->clear();

    auto channels = coreInterface->channels();

    q->addItem("None");

    auto& handles = channels[typeID];

    std::vector<tp_utils::StringID> names;
    names.reserve(handles.size());
    for(const auto& h : handles)
      names.push_back(h.first);

    qSort(names.begin(), names.end(), tp_utils::lessThanStringID);
    for(const tp_utils::StringID& name : names)
    {
      const tp_control::CoreInterfaceHandle& handle = handles[name];
      q->addItem(QString::fromStdString(handle.nameID().keyString()));

      if(selectedChannel == handle)
        q->setCurrentIndex(q->count() - 1);
    }

    q->blockSignals(false);
  }
};

//##################################################################################################
SelectChannelCombo::SelectChannelCombo(tp_control::CoreInterface* coreInterface, const tp_utils::StringID& typeID, QWidget* parent):
  QComboBox(parent),
  d(new Private(this, coreInterface, typeID))
{
  connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(currentIndexChangedSlot(QString)));
}

//##################################################################################################
SelectChannelCombo::~SelectChannelCombo()
{
  delete d;
}

//##################################################################################################
const tp_control::CoreInterfaceHandle& SelectChannelCombo::selectedChannel()const
{
  return d->selectedChannel;
}

//##################################################################################################
void SelectChannelCombo::setSelectedChannel(const tp_utils::StringID& channelNameID)
{
  d->selectedChannel = d->coreInterface->handle(d->typeID, channelNameID);
  d->updateList();
}

//##################################################################################################
tp_control::CoreInterface* SelectChannelCombo::coreInterface() const
{
  return d->coreInterface;
}

//##################################################################################################
void SelectChannelCombo::currentIndexChangedSlot(const QString& text)
{
  static const QString none("None");

  if(text == none)
    d->selectedChannel = tp_control::CoreInterfaceHandle();
  else
    d->selectedChannel = d->coreInterface->handle(d->typeID, text.toStdString());

  emit selectedChannelChanged(d->selectedChannel);
}

}
