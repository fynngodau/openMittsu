#ifndef OPENMITTSU_TASKS_SETFEATURELEVELCALLBACKTASK_H_
#define OPENMITTSU_TASKS_SETFEATURELEVELCALLBACKTASK_H_

#include "src/crypto/BasicCryptoBox.h"
#include "src/messages/MessageWithEncryptedPayload.h"
#include "src/protocol/ContactId.h"
#include "src/protocol/FeatureLevel.h"
#include "src/network/ServerConfiguration.h"

#include "src/tasks/CallbackTask.h"
#include "src/tasks/CertificateBasedCallbackTask.h"

#include <QString>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QSslCertificate>
#include <memory>

namespace openmittsu {
	namespace tasks {

		class SetFeatureLevelCallbackTask : public CertificateBasedCallbackTask, public CallbackTask {
		public:
			SetFeatureLevelCallbackTask(std::shared_ptr<openmittsu::network::ServerConfiguration> const& serverConfiguration, openmittsu::crypto::BasicCryptoBox const& cryptoBox, openmittsu::protocol::ContactId const& ownId, openmittsu::protocol::FeatureLevel const& featureLevel);
			virtual ~SetFeatureLevelCallbackTask();

			openmittsu::protocol::FeatureLevel const& getFeatureLevelToSet() const;
		protected:
			virtual void taskRun() override;
		private:
			QString const m_urlString;
			QString const m_agentString;
			openmittsu::crypto::BasicCryptoBox m_cryptoBox;

			openmittsu::protocol::ContactId const m_contactId;
			openmittsu::protocol::FeatureLevel const m_featureLevelToSet;
		};

	}
}

#endif // OPENMITTSU_TASKS_SETFEATURELEVELCALLBACKTASK_H_
