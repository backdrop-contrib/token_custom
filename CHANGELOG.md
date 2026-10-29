# Changelog

## 1.x-1.4.1 (2026-10-29)

Git tag: `1.x-1.4.1`.

### Fixed
- Saved token types load as objects: custom types show in the Token Browser, no PHP 8 warnings (#7, #6; PR #8 by dev-mm-distribution).
- A token that contains itself, directly or via other custom tokens, is left empty and logged instead of crashing the page.
- Delete button on the token and token type edit forms went to a broken confirmation path.
- Token format column no longer defaults to `php_code` (update 1001).
- Uninstall removes the whole `token_custom.settings` config file.

### Changed
- `.info`: dropped `package = Core` and the duplicate `type` line.
- README: Token Filter recommended for the "Replace tokens" filter; dropped the Fast Token Browser recommendation (in core since 1.30.0); "AI Assisted" credit; Security section.
- Docblocks in Backdrop format.

### Removed
- `token_custom.features.inc` (Backdrop has no Features module).

## 1.x-1.4.0 (2026-03-19)

### Changed
- Reworked to show custom tokens in the Fast Token Browser (#6).

## 1.x-1.3.1 (2024-11-19)

### Changed
- README: the PHP filter is not needed (#4).

## 1.x-1.3.0 (2023-09-14)

### Added
- First official Backdrop release.
