# installer for davisconsolehealthapi

import sys
import weewx

from weecfg.extension import ExtensionInstaller

def loader():

    return DavisConsoleHealthAPIInstaller()

class DavisConsoleHealthAPIInstaller(ExtensionInstaller):
    def __init__(self):
        super(DavisConsoleHealthAPIInstaller, self).__init__(
            version='0.30',
            name='davisconsolehealthapi',
            description='Collect and display station health information from the Davis Console API.',
            author='uajqq, KW',
            author_email='',
            data_services='user.davisconsolehealthapi.DavisConsoleHealthAPI',
            config = {
                'davisconsolehealthapi': {
                    'data_binding': 'davisconsolehealthapi_binding',
                    'station_id': '',
                    'api_key': '',
                    'api_secret': '',
                    '#max_age': 'None - default = 2592000',
                    'packet_log': '0',
                    '#packet_log': '0= first check and log available sensortypes once at start,  5= log all (packets ...)',
                },
                'DataBindings': {
                    'davisconsolehealthapi_binding': {
                        'database': 'davisconsolehealthapi_sqlite',
                        'table_name': 'archive',
                        'manager': 'weewx.manager.DaySummaryManager',
                        'schema': 'user.davisconsolehealthapi.schema'
                    }
                },
                'Databases': {
                    'davisconsolehealthapi_sqlite': {
                        'database_type': 'SQLite',
                        'database_name': 'davisconsolehealthapi.sdb'}
                },
                'StdReport': {
                    'DavisConsoleHealth': {
                        'skin': 'healthc',
                        'enable': 'True',
                        'HTML_ROOT': '/var/www/html/weewx/healthc'
                    },
                }
            },
            files=[('bin/user', ['bin/user/davisconsolehealthapi.py']),
                   ('skins/nws', ['skins/healthc/index.html.tmpl',
                    'skins/healthc/skin.conf',
                    'skins/healthc/healthc.css',
                    'skins/healthc/healthc.js',
                    'skins/healthc/favicon.ico',
                    'skins/healthc/sensors.inc',
                    'skins/healthc/titlebar.inc',
                    'skins/healthc/about.inc',
                    'skins/healthc/lang/de.conf',
                    'skins/healthc/lang/en.conf',
                    'skins/Seasons/healthc.inc',
                ]),
            ]
        )
