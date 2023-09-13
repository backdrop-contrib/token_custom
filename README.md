# Custom Tokens

It gives the user the ability to create custom tokens using standart input filters.
If the php filter is enabled, you can use php code to access token arguments (i.e. the $data array).

## Requirements:
No dependencies

## Installation:
Install this module using the official Backdrop CMS instructions at https://docs.backdropcms.org/documentation/extend-with-modules

## Documentation:
Visit admin/config/content/formats - configure the "Text formats" you want to use Tokens with and enable the "Replace Tokens" under the "Filter settings" section.

Visit the configuration page under admin/structure/token-custom or from the Admin bar go to "Structure" -> "Custom Tokens" and start creating the tokens you need.

To use the Token simply use [custom:<token__machine_name>]

You need to assign proper permissions to any role you would like to be able to create additional PHP tokens.

## TODO - Add documentation
Additional documentation is located in the Wiki: https://github.com/backdrop-contrib/token_custom/wiki

## Issues:
Bugs and Feature requests should be reported in the Issue Queue: https://github.com/backdrop-contrib/token_custom/issues

## Current Maintainer(s):
- [Steve Moorhouse (albanycomputers)] (https://github.com/albanycomputers)
- Seeking additional maintainers.

## Credits:

### Original Authors
This module is a fork of https://www.drupal.org/project/token_custom Version 7.x-2.0

Ariel Barreiro (hanoii) http://drupal.org/user/23157
abarrei@gmail.com

Rodolfo Ripado (gaspaio) http://drupal.org/user/545538
ggaspaio@gmail.com

## Sponsorship:
 - [Albany Computer Services] (https://www.albany-computers.co.uk)
 - [Albany Web Design] (https://www.albanywebdesign.co.uk)
 - [Albany Hosting] (https://www.albany-hosting.co.uk)

## License
This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.