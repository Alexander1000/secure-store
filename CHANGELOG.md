# Changelog secure-store

## @TODO for release:
- close current database (for open other file)
- generate passwords
- show page: refactor grid to set of controls
- add category for secrets and tree of categories

## 0.0.2 (Unreleased)

 * remove tree-list control for list secrets
 * `getPanelOpenFile` - use dynamic allocation vars for more stable
 * `getPanelNewFile` - use dynamic allocation vars for more stable
 * db open/save use `const char*` as arguments

## 0.0.1

 * desktop application with minimal usable functions:
   * open *.xdb files
   * create *.xdb files
   * add new secrets
   * edit secrets
   * remove old secrets
 * support cypher algorithm aes_256_cbc
