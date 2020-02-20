# intelligente-ventilator
Sensors: LM335; BMP2080

De bedoeling is van een ventilatorsturing te bouwen die voorkomt dat de compressor van een inbouw ijskastje oververhit geraakt.  We maken hiervoor gebruik van een analoge sensor LM335.
Bij kamertemperatuur doet hij niks, maar wanneer de ruimte in de keukenkast oploopt gaat hij vanaf 25 graden langzaam beginnen te draaien (PWM) proportioneel tot bij een temperatuur van 40 graden waar hij 100 procent draait.
De werking wordt met een RGB LED weergeven.

