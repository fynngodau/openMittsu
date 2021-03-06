#include "src/database/DatabaseThreadWorker.h"

#include "src/database/SimpleDatabase.h"
#include "src/exceptions/InternalErrorException.h"
#include "src/exceptions/InvalidPasswordOrDatabaseException.h"
#include "src/utility/Logging.h"
#include "src/utility/MakeUnique.h"
#include "src/utility/QObjectConnectionMacro.h"

namespace openmittsu {
	namespace database {

		DatabaseThreadWorker::~DatabaseThreadWorker() {
			//
		}

		int DatabaseThreadWorker::openDatabase(QString const& filename, QString const& password, QDir const& mediaStorageLocation) {
			try {
				std::shared_ptr<openmittsu::database::Database> newDatabase = std::make_shared<openmittsu::database::SimpleDatabase>(filename, password, mediaStorageLocation);
				if (newDatabase) {
					m_database = newDatabase;
					
					//result.failureReason = DatabaseOpenFailureReason::FREASON_NO_ERROR;
					//result.success = true;

					return 0;
				} else {
					//result.failureReason = DatabaseOpenFailureReason::FREASON_UNKNOWN;
					//result.success = false;

					return 2;
				}
			} catch (openmittsu::exceptions::InvalidPasswordOrDatabaseExceptionImpl&) {
				//result.failureReason = DatabaseOpenFailureReason::FREASON_INVALID_PASSWORD;
				//result.success = false;

				return 1;
			} catch (openmittsu::exceptions::InternalErrorExceptionImpl&) {
				//result.failureReason = DatabaseOpenFailureReason::FREASON_OTHER;
				//result.success = false;

				return 3;
			}
		}

		bool DatabaseThreadWorker::createDatabase(QString const& filename, openmittsu::protocol::ContactId const& selfContact, openmittsu::crypto::KeyPair const& selfLongTermKeyPair, QString const& password, QDir const& mediaStorageLocation) {
			std::shared_ptr<openmittsu::database::Database> newDatabase = std::make_shared<openmittsu::database::SimpleDatabase>(filename, selfContact, selfLongTermKeyPair, password, mediaStorageLocation);
			if (newDatabase) {
				m_database = newDatabase;
				return true;
			} else {
				LOGGER()->warn("Failed to create database!");
				return false;
			}
		}

		bool DatabaseThreadWorker::hasDatabase() const {
			return m_database != nullptr;
		}

		std::shared_ptr<openmittsu::database::Database> DatabaseThreadWorker::getDatabase() {
			return m_database;
		}

		std::shared_ptr<openmittsu::database::Database> const& DatabaseThreadWorker::getDatabase() const {
			return m_database;
		}

	}
}
