# Secure Store

Application for store ciphered secrets in local file.

## How build

```shell
cmake .
make
```

If problems with openssl on Mac OS, try it fix:
```shell
cmake -DOPENSSL_ROOT_DIR=$(brew --prefix openssl) -DOPENSSL_LIBRARIES=$(brew --prefix openssl)/lib .
```
