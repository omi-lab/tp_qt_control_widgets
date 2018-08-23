#include "tdp_control_widgets/SelectChannelComboAndButton.h"
#include "tdp_control_widgets/SelectChannelCombo.h"

#include "tp_control/CoreInterface.h"

#include "tp_validation/StringValidation.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

namespace tdp_control_widgets
{

//##################################################################################################
struct SelectChannelComboAndButton::Private
{
  SelectChannelCombo* combo{nullptr};
};

//##################################################################################################
SelectChannelComboAndButton::SelectChannelComboAndButton(tp_control::CoreInterface* coreInterface, const tp_utils::StringID& typeID, QWidget* parent):
  d(new Private())
{
  auto l = new QHBoxLayout(this);
  l->setContentsMargins(0,0,0,0);

  d->combo = new SelectChannelCombo(coreInterface, typeID, parent);
  l->addWidget(d->combo);

  auto addButton = new QPushButton("Add");
  l->addWidget(addButton);

  connect(addButton, &QPushButton::clicked, [&, typeID]()
  {
    std::string channelName = QInputDialog::getText(this->parentWidget(), "Channel Name", "Enter a name for the channel.").toStdString();
    channelName = tp_validation::cleanAlphaNumericSpaceUnderscore(channelName);

    if(channelName.empty())
      return;

    tp_utils::StringID nameID = channelName;

    std::unordered_map<tp_utils::StringID, std::unordered_map<tp_utils::StringID, tp_control::CoreInterfaceHandle>> channels = d->combo->coreInterface()->channels();
    if(tpContainsKey(channels[typeID], nameID))
    {
      QMessageBox::critical(this->parentWidget(), "Error", "Selected name already exists!");
      return;
    }

    d->combo->coreInterface()->handle(typeID, nameID);
    d->combo->setSelectedChannel(nameID);
  });

  connect(d->combo, &SelectChannelCombo::selectedChannelChanged, this, &SelectChannelComboAndButton::selectedChannelChanged);
}

//##################################################################################################
SelectChannelComboAndButton::~SelectChannelComboAndButton()
{
  delete d;
}

//##################################################################################################
const tp_control::CoreInterfaceHandle& SelectChannelComboAndButton::selectedChannel()const
{
  return d->combo->selectedChannel();
}

//##################################################################################################
void SelectChannelComboAndButton::setSelectedChannel(const tp_utils::StringID& channelNameID)
{
  d->combo->setSelectedChannel(channelNameID);
}

//##################################################################################################
tp_control::CoreInterface* SelectChannelComboAndButton::coreInterface() const
{
  return d->combo->coreInterface();
}

}
