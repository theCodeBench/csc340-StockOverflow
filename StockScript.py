from time import sleep
import os, sys, argparse

# Global constants
URL1 = 'https://www.nasdaq.com/symbol/'
URL2 = '/historical'
STOCK_SYMBOLS = (
    'aal','aapl','adbe','adi','adp','adsk','akam','algn','alxn','amat',
    'amgn','amzn','atvi','avgo','axp','ba','bidu','biib', 'bmrn','ca',
    'cat','celg','cern','chkp','chtr','cmcsa','cost','csco','csx','ctas',
    'ctrp','ctsh','ctxs','cvx','dis','disca','disck','dish','dltr','ea',
    'ebay','esrx','expe','fast','fb','fisv','fox','foxa','ge','gild',
    'goog','googl','gs','has','hd','holx','hsic','ibm','idxx','ilmn',
    'incy','intc','intu','isrg','jbht','jd','jnj','jpm','khc','klac',
    'ko','lbtya','lbtyk','lrcx','mar','mat','mcd','mchp','mdlz','meli',
    'mmm','mnst','mrk','msft','mu','mxim','myl','nclh','nflx','nke',
    'ntes','nvda','orly','payx','pcar','pcln','pfe','pg','pypl','qcom',
    'qvca','regn','rost','sbux','shpg','siri','stx','swks','symc','tmus',
    'trv','tsco','tsla','txn','ulta','unh','utx','v','viab','vod',
    'vrsk','vrtx','vz','wba','wdc','wmt','wynn','xlnx','xom','xray'
)

# Command line flag stuff
parser = argparse.ArgumentParser(description='Download stock info and parse into file.')
parser.add_argument('-d', action='store_true', help='Flag for downloading the files.')
parser.add_argument('-p', action='store_true', help='Flag for parsing the existing files (downloaded files if -d flag is set).')
parser.add_argument('-r', action='store_true', help='Flag for deleting the existing html files after downloading and processing.')

args = vars(parser.parse_args(sys.argv[1:]))

# HTML File download section
if args['d']:
    os.system('echo Downloading...')
    # Delete existing html directory
    os.system('rm -rf html/')
    # Make new empty directory
    os.system('mkdir html')
    # Download each html file based on symbols in global constant
    for symbol in STOCK_SYMBOLS:
        os.system('curl ' + URL1 + symbol + URL2 + ' > html/' + symbol + '.html')
        # Don't get blacklisted
        sleep(1)
    os.system('echo Done.')

# HTML File parsing section
if args['p']:
    os.system('echo Parsing...')
    # Use temporary file for parsing each html file
    os.system('ls html > temp.txt')
    files = open('temp.txt')
    tmp = files.read()
    files.close()
    # Get each file in html directory in list
    files = tmp.split('\n')[:-1]
    
    # Open file for writing
    os.system('touch StockFile.txt')
    output = open('StockFile.txt', 'w')

    for sfile in files:
        # Finds the current price using regex
        os.system('cp html/' + sfile + ' processInfo')
        os.system('./StockScriptHelper')
        
        # Use temporary file for getting price
        res = open('temp.txt')
        day = res.read().split('\n')[:60]
        for i in range(len(day)):
            day[i] = day[i][:-1]
        day = ';\n\t'.join(day)
        
        res.close()
        # Format output file correctly
        # Format for each line is symb:12.50
        res = sfile[:-5] + '{\n\t' + day + '\n}\n'
        output.write(res)

    output.close()
    # Get rid of temporary file
    os.system('rm -f temp.txt')
    os.system('echo Done.')
    
    
# Delete HTML Files
if args['r']:
    os.system('echo Deleting html directory...')
    os.system('rm -rf html/')
    os.system('echo Done.')
    
