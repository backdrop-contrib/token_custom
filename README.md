# Custom Tokens

Custom Tokens allows users to define their own tokens via the administrative UI using standard input filters. These tokens can then be used throughout the site in any field that supports token replacement.

## Requirements
- No hard dependencies.
- **Recommended:** [Fast Token Browser](https://backdropcms.org/project/fast_token_browser) (standard in many Backdrop installations) for an improved UI when selecting tokens.

## Installation
Install this module using the official Backdrop CMS instructions at [https://docs.backdropcms.org/documentation/extend-with-modules](https://docs.backdropcms.org/documentation/extend-with-modules).

## Configuration and Usage
1. **Text Formats:** Visit `Configuration > Content authoring > Text editors and formats` (`admin/config/content/formats`). Ensure the "Replace Tokens" filter is enabled for the text formats you intend to use.
2. **Creating Tokens:** Navigate to `Structure > Custom Tokens` (`admin/structure/token-custom`).
3. **Nesting:** You can use existing site tokens (like `[site:name]`) inside your custom token content.
4. **Placement:** Use your custom token anywhere tokens are accepted using the syntax `[custom:your_machine_name]`.

### Pro-Tip: Avoiding Paragraph Tags in Snippets
If you are creating "Inline" tokens (like a Company address "Line1, Line 2, Area, City, Zip Code") and find that they are being wrapped in `<p>` tags:
- Go to `Configuration > Content authoring > Text editors and formats` (`admin/config/content/formats`) and create a "Plain" or "Snippet" text format.
- Ensure "Convert line breaks into HTML (i.e. <br> and <p>)" is **disabled** for that format.
- Set the Editor to "None" for that format.
- When creating your custom token, select this new format to ensure the output is returned as raw text without HTML wrappers.

**Note:** As of version 1.x-1.3, PHP execution within tokens is no longer supported in favor of Backdrop security best practices.

## Documentation
Additional documentation is located in the Wiki: [https://github.com/backdrop-contrib/token_custom/wiki](https://github.com/backdrop-contrib/token_custom/wiki)

## Issues
Bugs and Feature requests should be reported in the Issue Queue: [https://github.com/backdrop-contrib/token_custom/issues](https://github.com/backdrop-contrib/token_custom/issues)

## Maintainer(s)
- [Steve Moorhouse (albanycomputers)](https://github.com/albanycomputers)
- Additional maintainers welcomed.

## Credits:
- Steve Moorhouse - Zulip (DrAlbany)
- Google Gemini 3.1 assisted with the coding of this module.

### Original Authors
This module is a port of the Drupal [Custom Tokens](https://www.drupal.org/project/token_custom) module.
- Ariel Barreiro (hanoii)
- Rodolfo Ripado (gaspaio)

## Sponsorship
- [Albany Computer Services](https://www.albany-computers.co.uk)
- [Albany Web Design](https://www.albanywebdesign.co.uk)
- [Albany Hosting](https://www.albany-hosting.co.uk)

## License
This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.