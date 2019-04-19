import matplotlib.pyplot as plt
import numpy as np
import wavinfo as wv


def framing(signal, rate, frame_size, frame_stride):
    frame_length, frame_step = frame_size * rate, frame_stride * rate
    signal_length = len(signal)
    frame_length = int(round(frame_length))
    frame_step = int(round(frame_step))
    num_frames = int(
        np.ceil(float(np.abs(signal_length - frame_length)) /
                frame_step))  # Make sure that we have at least 1 frame
    pad_signal_length = num_frames * frame_step + frame_length
    z = np.zeros((pad_signal_length - signal_length))
    pad_signal = np.append(signal, z)

    indices = np.tile(np.arange(0, frame_length), (num_frames, 1)) + np.tile(
        np.arange(0, num_frames * frame_step, frame_step), (frame_length, 1)).T
    frames = pad_signal[indices.astype(np.int32, copy=False)]
    return frames


def getff(path):
    data, time, rate, nframes = wv.read_wav(path)
    data = data * 1.0 / (max(abs(data)))
    pre_emphasis = 0.97
    emphasized_signal = np.append(data[0], data[1:] - pre_emphasis * data[:-1])
    frames = framing(emphasized_signal, rate, 0.025, 0.010)
    NFFT = 512
    print(frames.shape)
    frames *= np.hamming(len(frames[0]))
    print(frames.shape)
    mag_frames = np.absolute(np.fft.rfft(frames, NFFT))
    pow_frames = ((1.0 / NFFT) * ((mag_frames)**2))  # Power Spectrum
    return pow_frames


def getfflist(path):
    data = getff(path)
    hk = []
    for v in data:
        tmp = []
        tmp.append(np.argmax(v[:40]))
        tmp.append(np.argmax(v[40:80]) + 40)
        tmp.append(np.argmax(v[80:120]) + 80)
        tmp.append(np.argmax(v[120:180]) + 120)
        hk.append(tmp)
    return hk


v1 = getfflist("record2.wav")
v2 = getfflist("record3.wav")

file = open('data1.txt', 'w')
for line in v1:
    file.write(str(line) + "\n")
file.close()

file = open('data2.txt', 'w')
for line in v2:
    file.write(str(line) + "\n")
file.close()

# for it in v1:
#     if len(it):
#         print(it)
#         break
# for jt in v2:
#     if len(jt):
#         print(jt)
#         break
