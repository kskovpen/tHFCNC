from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'REQUESTNAME'
config.section_('JobType')
config.JobType.psetName = '../step2_PAT.py'
#config.JobType.inputFiles = ['../minbias.root']
#config.JobType.outputFiles = ['output.root']
#config.JobType.pyCfgParams = ['isData=0']
###config.JobType.maxMemoryMB = 4000
config.section_('Data')
config.Data.totalUnits = -1
config.Data.unitsPerJob = 50
config.Data.splitting = 'FileBased'
config.Data.publication = True
config.Data.inputDataset = 'INPUTDATASET'
config.Data.inputDBS = 'phys03'
#config.Data.inputDBS = 'global'
config.Data.publishDataName = 'PUBLISHDATANAME'
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter'
config.Data.outLFN = 'OUTLFN'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_FR_IPHC'
