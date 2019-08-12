import wave as wv
import numpy as np


def wav_read(path, sec):
    wavfile = wv.open(path, 'rb')
    params = wavfile.getparams()
    print(params)
    framesra = params[2]
    # print(params)
    datawav = wavfile.readframes(framesra * sec)
    wavfile.close()
    datause = np.fromstring(datawav, dtype=np.short)
    # datause = datause * 1.0 / (max(abs(datause)))

    # print(len(datause))
    # time = np.arange(0, framesra * sec) * (1.0 / framesra)
    return datause, framesra


def read_wav(path):
    wavfile = wv.open(path, 'rb')
    params = wavfile.getparams()
    print(params)
    rate = params[2]
    nframes = params[3]
    datawav = wavfile.readframes(nframes)
    wavfile.close()
    if params[1] == 2:
        datause = np.fromstring(datawav, dtype=np.short)
    else:
        datause = np.fromstring(datawav, dtype=np.byte)
    # datause = datause * 1.0 / (max(abs(datause)))

    # print(len(datause))
    time = np.arange(0, nframes) * (1.0 / rate)
    return datause, time, rate, nframes
