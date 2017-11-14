#ifndef OPENMITTSU_MESSAGES_MESSAGEFLAGSFACTORY_H_
#define OPENMITTSU_MESSAGES_MESSAGEFLAGSFACTORY_H_

#include "src/messages/MessageFlags.h"

namespace openmittsu {
	namespace messages {

		class MessageFlagsFactory {
		public:
			static MessageFlags createContactMessageFlags();
			static MessageFlags createGroupTextMessageFlags();
			static MessageFlags createGroupControlMessageFlags();
			static MessageFlags createTypingStatusMessageFlags();
			static MessageFlags createReceiptMessageFlags();
		private:
			// Disable the constructors
			MessageFlagsFactory();
			MessageFlagsFactory(MessageFlagsFactory const& other);
			virtual ~MessageFlagsFactory();
		};

	}
}

#endif // OPENMITTSU_MESSAGES_MESSAGEFLAGSFACTORY_H_
