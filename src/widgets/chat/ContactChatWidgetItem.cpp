#include "src/widgets/chat/ContactChatWidgetItem.h"

#include <QMenu>
#include <QAction>
#include <QClipboard>

#include "src/utility/QObjectConnectionMacro.h"

namespace openmittsu {
	namespace widgets {

		ContactChatWidgetItem::ContactChatWidgetItem(openmittsu::dataproviders::BackedContactMessage const& message, QWidget* parent) : ChatWidgetItem(message.getContact(), message.isMessageFromUs(), parent), m_contactMessage(message) {
			OPENMITTSU_CONNECT(&m_contactMessage, messageDataChanged(), this, onMessageDataChanged());
		}

		ContactChatWidgetItem::~ContactChatWidgetItem() {
			//
		}

		void ContactChatWidgetItem::showContextMenu(const QPoint& pos) {
			QPoint globalPos = mapToGlobal(pos);
			QMenu listMessagesContextMenu;

			QAction* actionSend = nullptr;
			QAction* actionReceived = nullptr;
			QAction* actionSeen = nullptr;
			QAction* actionAgree = nullptr;
			QAction* actionMessageId = nullptr;
			QAction* actionCopy = nullptr;

			openmittsu::protocol::MessageTime const sendTime = m_contactMessage.getSentAt();
			openmittsu::protocol::MessageTime const receivedTime = m_contactMessage.getReceivedAt();
			openmittsu::protocol::MessageTime const seenTime = m_contactMessage.getSeenAt();
			openmittsu::protocol::MessageTime const modifiedTime = m_contactMessage.getModifiedAt();
			openmittsu::dataproviders::messages::UserMessageState const messageState = m_contactMessage.getMessageState();

			if (!sendTime.isNull()) {
				actionSend = new QAction(QString("Sent: %1").arg(sendTime.getTime().toString(QStringLiteral("HH:mm:ss, on dd.MM.yyyy"))), &listMessagesContextMenu);
			} else {
				actionSend = new QAction(QString("Sent: -unknown-"), &listMessagesContextMenu);
			}
			listMessagesContextMenu.addAction(actionSend);
			if (!receivedTime.isNull()) {
				actionReceived = new QAction(QString("Received: %1").arg(receivedTime.getTime().toString(QStringLiteral("HH:mm:ss, on dd.MM.yyyy"))), &listMessagesContextMenu);
			} else {
				actionReceived = new QAction(QString("Received: -unknown-"), &listMessagesContextMenu);
			}
			listMessagesContextMenu.addAction(actionReceived);
			if (!seenTime.isNull()) {
				actionSeen = new QAction(QString("Seen: %1").arg(seenTime.getTime().toString(QStringLiteral("HH:mm:ss, on dd.MM.yyyy"))), &listMessagesContextMenu);
			} else {
				actionSeen = new QAction(QString("Seen: -unknown-"), &listMessagesContextMenu);
			}
			listMessagesContextMenu.addAction(actionSeen);


			if (messageState == openmittsu::dataproviders::messages::UserMessageState::USERACK) {
				actionAgree = new QAction(QString("Agreed: %1").arg(modifiedTime.getTime().toString(QStringLiteral("HH:mm:ss, on dd.MM.yyyy"))), &listMessagesContextMenu);
			} else if (messageState == openmittsu::dataproviders::messages::UserMessageState::USERDEC) {
				actionAgree = new QAction(QString("Disagreed: %1").arg(modifiedTime.getTime().toString(QStringLiteral("HH:mm:ss, on dd.MM.yyyy"))), &listMessagesContextMenu);
			} else {
				actionAgree = new QAction(QString("Not agreed/disagreed"), &listMessagesContextMenu);
			}
			listMessagesContextMenu.addAction(actionAgree);

			actionMessageId = new QAction(QString("Message ID: #%1").arg(m_contactMessage.getMessageId().toQString()), &listMessagesContextMenu);
			listMessagesContextMenu.addAction(actionMessageId);

			actionCopy = new QAction(QString("Copy to Clipboard"), &listMessagesContextMenu);
			listMessagesContextMenu.addAction(actionCopy);

			appendCustomContextMenuEntries(pos, listMessagesContextMenu);

			QAction* selectedItem = listMessagesContextMenu.exec(globalPos);
			if (selectedItem != nullptr) {
				if (!handleCustomContextMenuEntrySelection(selectedItem)) {
					if (selectedItem == actionSend) {
						//
					} else if (selectedItem == actionSeen) {
						//
					} else if (selectedItem == actionReceived) {
						//
					} else if (selectedItem == actionAgree) {
						//
					} else if (selectedItem == actionCopy) {
						copyToClipboard();
					}
				}
			}
		}

		openmittsu::dataproviders::BackedMessage& ContactChatWidgetItem::getMessage() {
			return m_contactMessage;
		}

		openmittsu::dataproviders::BackedMessage const& ContactChatWidgetItem::getMessage() const {
			return m_contactMessage;
		}

	}
}
