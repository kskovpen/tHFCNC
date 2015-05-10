# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial#Output_dataset_publication
from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
#config.General.requestName = 'REQUESTNAME'
config.section_('JobType')
config.JobType.generator = 'lhe'
config.JobType.psetName = '../prod_LHEtoRECO.py'
config.JobType.pluginName = 'PrivateMC'
#config.JobType.inputFiles = ['../minbias.root']
#config.JobType.outputFiles = ['output.root']
#config.JobType.pyCfgParams = ['isData=0']
config.JobType.maxMemoryMB = 4000
config.section_('Data')
#config.Data.totalUnits = 5
#config.Data.totalUnits = 2000000
config.Data.totalUnits = 1000000
#config.Data.unitsPerJob = 1
config.Data.unitsPerJob = 1000
config.Data.splitting = 'EventBased'
config.Data.publication = True
config.Data.primaryDataset = 'tHFCNC13TeV'
config.Data.publishDataName = 'VERSION'
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter'
config.Data.outLFN = 'OUTLFN'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_FR_IPHC'
