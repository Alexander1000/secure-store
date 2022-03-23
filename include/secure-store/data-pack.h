#ifndef H_SECURE_STORE_DATA_PACK
#define H_SECURE_STORE_DATA_PACK

namespace SecureStore
{
    class DataPack
    {
    public:
        DataPack(int, void*);

        int getLength();
        void* getData();
    private:
        int length;
        void* data;
    };
}

#endif
