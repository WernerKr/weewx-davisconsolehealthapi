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
            description='Collect and display station health information from the Davis Weatherlink Console 6313 API.',
            author='Krenn Werner',
            author_email='',
            data_services='user.davisconsolehealthapi.DavisConsoleHealthAPI',
            config = {
                'davisconsolehealthapi': {
                    'data_binding': 'davisconsolehealthapi_binding',
                    'station_id': '99999',
                    'api_key': 'abcdefghijklmnopqrstuvwzyx123456',
                    'api_secret': '123456abcdefghijklmnopqrstuvwxyz',
                    'max_age': 'None',
                    'packet_log': '0',
                },
                'Engine': {
                    'Services': {
                        'data_services': 'user.davisconsolehealthapi.DavisConsoleHealthAPI,',
                    }
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
                'Accumulator': {
                    'consoleRadioVersionC': {
                        'accumulator': 'firstlast',
                        'extractor': 'last'},
                    'consoleSwVersionC': {
                        'accumulator': 'firstlast',
                        'extractor': 'last'},
                    'consoleOsVersionC': {
                        'accumulator': 'firstlast',
                        'extractor': 'last'}
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
