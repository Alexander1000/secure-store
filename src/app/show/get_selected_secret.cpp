#include <secure-store.h>

namespace SecureStore::Application
{
    SecureStore::Storage::Record* ShowFrame::getSelectedSecret()
    {
        if (this->selectedSecretIndex < 0
            || this->storage == nullptr
            || this->storage->getRecords() == nullptr
            || this->storage->getRecords()->empty()
            || this->selectedSecretIndex >= this->storage->getRecords()->size()) {
            return nullptr;
        }

        SecureStore::Storage::Record* secret = nullptr;
        int index = 0;

        for (auto & it : *this->storage->getRecords()) {
            auto record = it->getRecord();

            if (index == this->selectedSecretIndex) {
                secret = record;
                break;
            }

            index++;
        }

        return secret;
    }
}
