#ifndef OPENMITTSU_MESSAGES_CONTACT_USERTYPINGMESSAGECONTENT_H_
#define OPENMITTSU_MESSAGES_CONTACT_USERTYPINGMESSAGECONTENT_H_

#include "src/messages/MessageContentFactory.h"
#include "src/messages/contact/ContactMessageContent.h"

#include <QByteArray>

namespace openmittsu {
	namespace messages {
		namespace contact {

			class UserTypingMessageContent : public ContactMessageContent {
			public:
				UserTypingMessageContent(bool isTyping);
				virtual ~UserTypingMessageContent();

				virtual bool isUserTyping() const;

				virtual ContactMessageContent* clone() const override;

				virtual QByteArray toPacketPayload() const override;

				virtual MessageContent* fromPacketPayload(FullMessageHeader const& messageHeader, QByteArray const& payload) const override;

				friend class TypedMessageContentFactory <UserTypingMessageContent>;
			private:
				bool isTyping;

				static bool registrationResult;

				UserTypingMessageContent();
			};

		}
	}
}

#endif // OPENMITTSU_MESSAGES_CONTACT_USERTYPINGMESSAGECONTENT_H_
