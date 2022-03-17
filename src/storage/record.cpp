#include <secure-store.h>

#include <string>
#include <list>

namespace SecureStore::Storage
{
    Record::Record()
    {
        this->id = 0;
        this->name = nullptr;
        this->user = nullptr;
        this->password = nullptr;
        this->comment = nullptr;
        this->keywords = nullptr;
        this->createTime = 0;
    }

    uint16_t Record::getId()
    {
        return this->id;
    }

    std::string* Record::getName()
    {
        return this->name;
    }

    std::string* Record::getUser()
    {
        return this->user;
    }

    std::string* Record::getPassword()
    {
        return this->password;
    }

    std::string* Record::getComment()
    {
        return this->comment;
    }

    std::list<std::string>* Record::getKeywords()
    {
        return this->keywords;
    }

    uint64_t Record::getCreateTime()
    {
        return this->createTime;
    }

    void Record::setId(uint16_t id)
    {
        this->id = id;
    }

    void Record::setName(std::string *name)
    {
        this->name = name;
    }

    void Record::setUser(std::string *user)
    {
        this->user = user;
    }

    void Record::setPassword(std::string *password)
    {
        this->password = password;
    }

    void Record::setComment(std::string *comment)
    {
        this->comment = comment;
    }

    void Record::setKeywords(std::list<std::string> *keywords)
    {
        this->keywords = keywords;
    }

    void Record::setCreateTime(uint64_t createTime)
    {
        this->createTime = createTime;
    }
}
