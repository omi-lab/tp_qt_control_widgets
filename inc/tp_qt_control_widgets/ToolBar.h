#ifndef tp_qt_control_ToolBar_h
#define tp_qt_control_ToolBar_h

#include "tp_qt_control_widgets/Globals.h"

#include <QToolBar>

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
//! A tool bar that updates a channel in the core interface
/*!
This class provides a tool bar that changes the value of a channel base on the tool button that is
currently checked.

The tool bar will both set the value of the channel and respond to changes in that channel, updating
the check state of its buttons accordingly.
*/
class tp_qt_CONTROL_WIDGETS_SHARED_EXPORT ToolBar: public QToolBar
{
  Q_OBJECT
public:
  //################################################################################################
  //! Construct a tool bar
  /*!
  \param coreInterface - The core interface that contains the channel that will be controled.
  \param channel
  \param parent
  */
  ToolBar(tp_control::CoreInterface* coreInterface,
          const tp_control::CoreInterfaceHandle& channel,
          QWidget* parent=nullptr);

  //################################################################################################
  //! Destructor
  virtual ~ToolBar();

  //################################################################################################
  //! Add a button to the tool bar
  /*!
  \param icon - The icon to go on the button.
  \param toolTip - The tool tip for the button.
  \param value - The value that the channel will be set to if the button is checked.
  */
  void addButton(const QString& icon, const QString& toolTip, const tp_utils::StringID& value);

private slots:
  //################################################################################################
  void buttonClicked(int index);

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
