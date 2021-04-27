# misc-projects
This is where miscellaneous projects go. 

# Jamulus Traffic Analyzer

This is a peice of software that takes the ouput of the jamulus traffic data file and does some analytical analysis of traffic, and shows
some general statistics over a specified date range. Not quite finished yet. Currently it identifies unique users and jam sessions and totals them up,
but there are bugs in getting correct time totals. 

## TODO:
1. Fix time bug, hours are not calculating corrently when jam times go past midnight
2. General Refactor to ease readability
3. Proper file path entry. Currently the read file is in a hardcoded location
4. Export analysis data as CSV
5. GUI?? (Perhaps Rebuild in Python.....?)
