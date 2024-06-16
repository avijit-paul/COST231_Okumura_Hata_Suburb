# import libraries

import pandas as pd
import numpy as np

def correction_factor(freq, m_h):           # m_h -> height of the mobile station b_h -> base station height
    if 150 < freq <= 200:
        return 8.29 * (np.log10(1.54 * m_h) ** 2) - 1.1
    elif frequency > 200:
        return 3.2 * (np.log10(11.75 * m_h) ** 2) - 4.97
    else:
        return 0.8 + (1.1 * np.log10(freq) - 0.7) * m_h - 1.56 * np.log10(freq)

def cost231_hata(freq, distance, b_h, m_h, city_size):  # city -> O for suburb, 1 for urban
    a_hm = correction_factor(freq, m_h)
    if city_size == 0:  # suburban
        path_loss = (46.3 + 33.9 * np.log10(freq) - 13.82 * np.log10(b_h) - 
                     a_hm + (44.9 - 6.55 * np.log10(b_h)) * np.log10(distance))
    else:  # Urban
        path_loss = (46.3 + 33.9 * np.log10(freq) - 13.82 * np.log10(b_h) - 
                     a_hm + (44.9 - 6.55 * np.log10(b_h)) * np.log10(distance) + 3)
    return path_loss


df = pd.read_excel('file_name.xlsx')


for index, row in df.iterrows():
    freq = row['Frequency (MHz)']
    distance = row['Distance (km)']
    b_h = row['Base Height (m)']
    m_h = row['Mobile Height (m)']
    city_size = row['City Size (0 or 1)']

    path_loss = cost231_hata(freq, distance, base_height, mobile_height, city_size) # path loss

    print(f"Frequency: {freq} MHz, Distance: {distance} km, Base Height: {b_h} m, "
          f"Mobile Height: {m_h} m, City Size: {'Small to Medium' if city_size == 0 else 'Metropolitan'}, "
          f"Path Loss: {path_loss:.2f} dB")
