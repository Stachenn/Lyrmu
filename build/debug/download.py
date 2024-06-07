import pytube
import sys
import pytube.exceptions
print(sys.argv[1])
file: pytube = pytube.YouTube(sys.argv[1])

try:
    fileSave = file.streams.filter(only_audio=True)
    
except pytube.exceptions.LiveStreamError:
    print("\nERROR: FOUNDED PROMPT IS STREAM")
    exit(1)

fileSave[0].download()