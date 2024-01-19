# Soldering Station for Yaxun Yx936m iron 

# Estación de soldadura para el soldador Yaxun Yx936m
### Article in spanish and english / Articulo en español e ingles

An "Economical" Soldering station for the Yaxun Yx936m Iron.
This is my first Serious project in arduino so please if you see errors and/or bad coding practices plese open an issue or make the changes in a commit.

Una estación de soldadura "económica" para el soldador Yaxun Yx936m.
Este es mi primer proyecto serio en arduino así que por favor si ves errores y / o malas prácticas de programación por favor abra un issue o haga los cambios en un commit.




## Author / Autor

- [@Voligoma](https://www.github.com/Voligoma)


## Documentation [Progression] / Documentación [Progreso]

### PinOut
The PinOut of the Iron is :

El Pinout del Soldador es:
![img](https://raw.githubusercontent.com/Voligoma/Soldering-station-for-Yaxun-Yx936m/main/img/Yaxun%20Yx936m%20PinOut.png)

Legend: 

PE : Protective earth goes directly to the metal part of the Iron

Heater : just the Heater its around 12 Ohm +/- 1 Ohm

Thermocuple : This specific type of thermocuple generates a pretty low voltage (a few mV) , since the arduino only reads 4.9mV per division (https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) we need an amplifier for the Arduino to read the small voltage .


Leyenda: 

PE : Tierra va directamente a la parte metálica del soldador

Calentador : solo el calentador su alrededor de 12 Ohm +/- 1 Ohm

Termocupla : Este tipo de termocupla especifico genera una pequeña tension (unos pocos mV) al momento de calentar necesitamos utilizar un pequeño amplificador para que el arduino lo pueda leer (El arduino tiene una resolución de 4.9 mV por división para más información: https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/ ).

### Amplifier / Amplificador
Section under work/ sección en proceso

As mentioned on the PinOut section we need to amplify the output of the thermocuple ,after some investigatión i'v come to a conclusion to use an non inverting OPAMP (Operational amplifier).

What the heck is an Operational Amplifier? Its a type of amplifier that is more stable than a transistor for some impedance stuff.
The formula to calculate the gain of the opamp is: 
![img](https://raw.githubusercontent.com/Voligoma/Soldering-station-for-Yaxun-Yx936m/main/img/CodeCogsEqn%20(1).png)

![img1](https://raw.githubusercontent.com/Voligoma/Soldering-station-for-Yaxun-Yx936m/main/img/Montage_AOP_non-inverseur.png)

 R1 = Ri R2 = Rf

 To calculate the gain needed we just divide the needed voltage by our voltage 

Como mencioné en la sección de pinout necesitamos amplificar la salida de la termocupla, despues de un poco de investigación llegué a la conclusión de que hay que usar un OPAMP (amplificador Operacional no invirtiente?).

Que carajo es un amplificador operacional? Es un tipo des amplificador que tiende a ser maás estable que un transistor deido a algunos temas de impadancia.

La formula para el calculo de ganancia es:
![img](https://raw.githubusercontent.com/Voligoma/Soldering-station-for-Yaxun-Yx936m/main/img/CodeCogsEqn%20(1).png)

![img1](https://raw.githubusercontent.com/Voligoma/Soldering-station-for-Yaxun-Yx936m/main/img/Montage_AOP_non-inverseur.png)

 R1 = Ri R2 = Rf

Para calcular la ganancia de solo debemos dividir la tension objetivo sobre nuestra tensión




## License / Licencia


[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

![GitHub commit activity](https://img.shields.io/github/commit-activity/t/Voligoma/Soldering-station-for-Yaxun-Yx936m)
