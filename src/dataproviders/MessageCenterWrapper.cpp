#include "src/dataproviders/MessageCenterWrapper.h"

#include "src/exceptions/InternalErrorException.h"
#include "src/utility/Logging.h"
#include "src/utility/MakeUnique.h"
#include "src/utility/QObjectConnectionMacro.h"
#include "src/utility/Wrapping.h"


namespace openmittsu {
	namespace dataproviders {

		MessageCenterWrapper::MessageCenterWrapper(MessageCenterPointerAuthority const* messageCenterPointerAuthority) : MessageCenter(), m_messageCenterPointerAuthority(messageCenterPointerAuthority), m_messageCenter() {
			OPENMITTSU_CONNECT_QUEUED(m_messageCenterPointerAuthority, newMessageCenterAvailable(), this, onMessageCenterPointerAuthorityHasNewMessageCenter());
			onMessageCenterPointerAuthorityHasNewMessageCenter();
		}

		MessageCenterWrapper::MessageCenterWrapper(MessageCenterWrapper const& other) : MessageCenter(), m_messageCenterPointerAuthority(other.m_messageCenterPointerAuthority), m_messageCenter() {
			OPENMITTSU_CONNECT_QUEUED(m_messageCenterPointerAuthority, newMessageCenterAvailable(), this, onMessageCenterPointerAuthorityHasNewMessageCenter());
			onMessageCenterPointerAuthorityHasNewMessageCenter();
		}

		MessageCenterWrapper::~MessageCenterWrapper() {
			//
		}

		bool MessageCenterWrapper::hasMessageCenter() const {
			auto ptr = m_messageCenter.lock();
			return (ptr) ? true : false;
		}

		void MessageCenterWrapper::onMessageCenterPointerAuthorityHasNewMessageCenter() {
			m_messageCenter = m_messageCenterPointerAuthority->getMessageCenterWeak();

			auto ptr = m_messageCenter.lock();
			if (ptr) {
				OPENMITTSU_CONNECT_QUEUED(ptr.get(), newUnreadMessageAvailableContact(openmittsu::protocol::ContactId const&), this, onNewUnreadMessageAvailableContact(openmittsu::protocol::ContactId const&));
				OPENMITTSU_CONNECT_QUEUED(ptr.get(), newUnreadMessageAvailableGroup(openmittsu::protocol::GroupId const&), this, onNewUnreadMessageAvailableGroup(openmittsu::protocol::GroupId const&));
				OPENMITTSU_CONNECT_QUEUED(ptr.get(), messageChanged(QString const&), this, onMessageChanged(QString const&));
			}
		}

		void MessageCenterWrapper::onNewUnreadMessageAvailableContact(openmittsu::protocol::ContactId const& contact) {
			emit newUnreadMessageAvailableContact(contact);
		}

		void MessageCenterWrapper::onNewUnreadMessageAvailableGroup(openmittsu::protocol::GroupId const& group) {
			emit newUnreadMessageAvailableGroup(group);
		}
		
		void MessageCenterWrapper::onMessageChanged(QString const& uuid) {
			emit messageChanged(uuid);
		}

		bool MessageCenterWrapper::sendAudio(openmittsu::protocol::ContactId const& receiver, QByteArray const& audio, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendAudio, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(QByteArray const&, audio), Q_ARG(quint16, lengthInSeconds));
		}

		bool MessageCenterWrapper::sendImage(openmittsu::protocol::ContactId const& receiver, QByteArray const& image, QString const& caption) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendImage, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(QByteArray const&, image), Q_ARG(QString const&, caption));
		}

		bool MessageCenterWrapper::sendLocation(openmittsu::protocol::ContactId const& receiver, openmittsu::utility::Location const& location) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendLocation, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(openmittsu::utility::Location const&, location));
		}

		bool MessageCenterWrapper::sendText(openmittsu::protocol::ContactId const& receiver, QString const& text) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendText, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(QString const&, text));
		}

		bool MessageCenterWrapper::sendVideo(openmittsu::protocol::ContactId const& receiver, QByteArray const& video, QByteArray const& coverImage, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendVideo, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(QByteArray const&, video), Q_ARG(QByteArray const&, coverImage), Q_ARG(quint16, lengthInSeconds));
		}

		bool MessageCenterWrapper::sendReceipt(openmittsu::protocol::ContactId const& receiver, openmittsu::protocol::MessageId const& receiptedMessageId, openmittsu::messages::contact::ReceiptMessageContent::ReceiptType const& receiptType) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendReceipt, bool, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(openmittsu::protocol::MessageId const&, receiptedMessageId), Q_ARG(openmittsu::messages::contact::ReceiptMessageContent::ReceiptType const&, receiptType));
		}

		void MessageCenterWrapper::sendUserTypingStatus(openmittsu::protocol::ContactId const& receiver, bool isTyping) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(sendUserTypingStatus, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(bool, isTyping));
		}

		bool MessageCenterWrapper::sendAudio(openmittsu::protocol::GroupId const& group, QByteArray const& audio, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendAudio, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QByteArray const&, audio), Q_ARG(quint16, lengthInSeconds));
		}

		bool MessageCenterWrapper::sendImage(openmittsu::protocol::GroupId const& group, QByteArray const& image, QString const& caption) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendImage, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QByteArray const&, image), Q_ARG(QString const&, caption));
		}

		bool MessageCenterWrapper::sendLeave(openmittsu::protocol::GroupId const& group) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendLeave, bool, Q_ARG(openmittsu::protocol::GroupId const&, group));
		}

		bool MessageCenterWrapper::sendLocation(openmittsu::protocol::GroupId const& group, openmittsu::utility::Location const& location) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendLocation, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::utility::Location const&, location));
		}

		bool MessageCenterWrapper::sendReceipt(openmittsu::protocol::GroupId const& group, openmittsu::protocol::MessageId const& receiptedMessageId, openmittsu::messages::contact::ReceiptMessageContent::ReceiptType const& receiptType) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendReceipt, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::MessageId const&, receiptedMessageId), Q_ARG(openmittsu::messages::contact::ReceiptMessageContent::ReceiptType const&, receiptType));
		}

		bool MessageCenterWrapper::sendSyncRequest(openmittsu::protocol::GroupId const& group) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendSyncRequest, bool, Q_ARG(openmittsu::protocol::GroupId const&, group));
		}

		bool MessageCenterWrapper::sendText(openmittsu::protocol::GroupId const& group, QString const& text) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendText, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QString const&, text));
		}

		bool MessageCenterWrapper::sendVideo(openmittsu::protocol::GroupId const& group, QByteArray const& video, QByteArray const& coverImage, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendVideo, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QByteArray const&, video), Q_ARG(QByteArray const&, coverImage), Q_ARG(quint16, lengthInSeconds));
		}

		bool MessageCenterWrapper::sendGroupCreation(openmittsu::protocol::GroupId const& group, QSet<openmittsu::protocol::ContactId> const& members) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendGroupCreation, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QSet<openmittsu::protocol::ContactId> const&, members));
		}

		bool MessageCenterWrapper::sendGroupTitle(openmittsu::protocol::GroupId const& group, QString const& title) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendGroupTitle, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QString const&, title));
		}

		bool MessageCenterWrapper::sendGroupImage(openmittsu::protocol::GroupId const& group, QByteArray const& image) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(sendGroupImage, bool, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(QByteArray const&, image));
		}

		void MessageCenterWrapper::setNetworkSentMessageAcceptor(std::shared_ptr<NetworkSentMessageAcceptor> const& newNetworkSentMessageAcceptor) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(setNetworkSentMessageAcceptor, Q_ARG(std::shared_ptr<NetworkSentMessageAcceptor> const&, newNetworkSentMessageAcceptor));
		}

		void MessageCenterWrapper::processMessageSendFailed(openmittsu::protocol::ContactId const& receiver, openmittsu::protocol::MessageId const& messageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processMessageSendFailed, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(openmittsu::protocol::MessageId const&, messageId));
		}

		void MessageCenterWrapper::processMessageSendDone(openmittsu::protocol::ContactId const& receiver, openmittsu::protocol::MessageId const& messageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processMessageSendDone, Q_ARG(openmittsu::protocol::ContactId const&, receiver), Q_ARG(openmittsu::protocol::MessageId const&, messageId));
		}

		void MessageCenterWrapper::processMessageSendFailed(openmittsu::protocol::GroupId const& group, openmittsu::protocol::MessageId const& messageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processMessageSendFailed, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::MessageId const&, messageId));
		}

		void MessageCenterWrapper::processMessageSendDone(openmittsu::protocol::GroupId const& group, openmittsu::protocol::MessageId const& messageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processMessageSendDone, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::MessageId const&, messageId));
		}

		void MessageCenterWrapper::processReceivedContactMessageAudio(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& audio, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageAudio, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, audio), Q_ARG(quint16, lengthInSeconds));
		}

		void MessageCenterWrapper::processReceivedContactMessageImage(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& image) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageImage, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, image));
		}

		void MessageCenterWrapper::processReceivedContactMessageLocation(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, openmittsu::utility::Location const& location) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageLocation, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(openmittsu::utility::Location const&, location));
		}

		void MessageCenterWrapper::processReceivedContactMessageText(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QString const& message) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageText, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QString const&, message));
		}

		void MessageCenterWrapper::processReceivedContactMessageVideo(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& video, QByteArray const& coverImage, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageVideo, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, video), Q_ARG(QByteArray const&, coverImage), Q_ARG(quint16, lengthInSeconds));
		}

		void MessageCenterWrapper::processReceivedContactMessageReceiptReceived(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageId const& referredMessageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageReceiptReceived, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageId const&, referredMessageId));
		}

		void MessageCenterWrapper::processReceivedContactMessageReceiptSeen(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageId const& referredMessageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageReceiptSeen, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageId const&, referredMessageId));
		}

		void MessageCenterWrapper::processReceivedContactMessageReceiptAgree(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageId const& referredMessageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageReceiptAgree, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageId const&, referredMessageId));
		}

		void MessageCenterWrapper::processReceivedContactMessageReceiptDisagree(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageId const& referredMessageId) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactMessageReceiptDisagree, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageId const&, referredMessageId));
		}

		void MessageCenterWrapper::processReceivedContactTypingNotificationTyping(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactTypingNotificationTyping, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent));
		}

		void MessageCenterWrapper::processReceivedContactTypingNotificationStopped(openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedContactTypingNotificationStopped, Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent));
		}

		void MessageCenterWrapper::processReceivedGroupMessageAudio(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& audio, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupMessageAudio, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, audio), Q_ARG(quint16, lengthInSeconds));
		}

		void MessageCenterWrapper::processReceivedGroupMessageImage(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& image) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupMessageImage, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, image));
		}

		void MessageCenterWrapper::processReceivedGroupMessageLocation(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, openmittsu::utility::Location const& location) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupMessageLocation, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(openmittsu::utility::Location const&, location));
		}

		void MessageCenterWrapper::processReceivedGroupMessageText(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QString const& message) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupMessageText, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QString const&, message));
		}

		void MessageCenterWrapper::processReceivedGroupMessageVideo(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& video, QByteArray const& coverImage, quint16 lengthInSeconds) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupMessageVideo, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, video), Q_ARG(QByteArray const&, coverImage), Q_ARG(quint16, lengthInSeconds));
		}

		void MessageCenterWrapper::processReceivedGroupCreation(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QSet<openmittsu::protocol::ContactId> const& members) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupCreation, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QSet<openmittsu::protocol::ContactId> const&, members));
		}

		void MessageCenterWrapper::processReceivedGroupSetImage(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QByteArray const& image) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupSetImage, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QByteArray const&, image));
		}

		void MessageCenterWrapper::processReceivedGroupSetTitle(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived, QString const& groupTitle) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupSetTitle, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived), Q_ARG(QString const&, groupTitle));
		}

		void MessageCenterWrapper::processReceivedGroupSyncRequest(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupSyncRequest, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived));
		}

		void MessageCenterWrapper::processReceivedGroupLeave(openmittsu::protocol::GroupId const& group, openmittsu::protocol::ContactId const& sender, openmittsu::protocol::MessageId const& messageId, openmittsu::protocol::MessageTime const& timeSent, openmittsu::protocol::MessageTime const& timeReceived) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(processReceivedGroupLeave, Q_ARG(openmittsu::protocol::GroupId const&, group), Q_ARG(openmittsu::protocol::ContactId const&, sender), Q_ARG(openmittsu::protocol::MessageId const&, messageId), Q_ARG(openmittsu::protocol::MessageTime const&, timeSent), Q_ARG(openmittsu::protocol::MessageTime const&, timeReceived));
		}

		void MessageCenterWrapper::addNewContact(openmittsu::protocol::ContactId const& contact, openmittsu::crypto::PublicKey const& publicKey) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(addNewContact, Q_ARG(openmittsu::protocol::ContactId const&, contact), Q_ARG(openmittsu::crypto::PublicKey const&, publicKey));
		}

		void MessageCenterWrapper::resendGroupSetup(openmittsu::protocol::GroupId const& group) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_VOID(resendGroupSetup, Q_ARG(openmittsu::protocol::GroupId const&, group));
		}

		bool MessageCenterWrapper::createNewGroupAndInformMembers(QSet<openmittsu::protocol::ContactId> const& members, bool addSelfContact, QVariant const& groupTitle, QVariant const& groupImage) {
			OPENMITTSU_MESSAGECENTERWRAPPER_WRAP_RETURN(createNewGroupAndInformMembers, bool, Q_ARG(QSet<openmittsu::protocol::ContactId> const&, members), Q_ARG(bool, addSelfContact), Q_ARG(QVariant const&, groupTitle), Q_ARG(QVariant const&, groupImage));
		}

	}
}
