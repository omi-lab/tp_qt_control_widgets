#ifndef tp_qt_control_widgets_SelectChannelComboAndButton_h
#define tp_qt_control_widgets_SelectChannelComboAndButton_h

#include "tp_qt_control_widgets/Globals.h"

#include <QWidget>

namespace tp_utils
{
class StringID;
}

namespace tp_control
{
class CoreInterface;
class CoreInterfaceHandle;
}

namespace tp_qt_control_widgets
{

//##################################################################################################
//! A combo box for selecting a channel from a core interface or creating one.
class tp_qt_CONTROL_WIDGETS_SHARED_EXPORT SelectChannelComboAndButton: public QWidget
{
  Q_OBJECT
public:
  //################################################################################################
  //! Construct a channel combo.
  /*!
  This will construct a channel combo box that will list all channels of typeID in the
  coreInterface.

  \param coreInterface - The core interface to get the channels from.
  \param typeID - The type of channel to list.
  \param parent - The parent widget.
  */
  SelectChannelComboAndButton(tp_control::CoreInterface* coreInterface, const tp_utils::StringID& typeID, QWidget* parent=nullptr);

  //################################################################################################
  //! Destructor.
  virtual ~SelectChannelComboAndButton();

  //################################################################################################
  //! Returns the currently selected channel.
  /*!
  This will return a handle to the channel that is currently selected in the combo.

  \return A handle to the selected channel.
  */
  const tp_control::CoreInterfaceHandle& selectedChannel()const;

  //################################################################################################
  //! Sets the selected channel.
  /*!
  The handle should point to a channel of the same type. This will select the channel and emit
  selectedChannelChanged().

  \param channelNameID - The handle of the channel to select.
  */
  void setSelectedChannel(const tp_utils::StringID& channelNameID);

  //################################################################################################
  tp_control::CoreInterface* coreInterface() const;

signals:
  //################################################################################################
  //! Emitted each time the channel selection changes.
  void selectedChannelChanged(const tp_control::CoreInterfaceHandle& selectedChannel);

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
