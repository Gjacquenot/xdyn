## Tutoriel 3 : génération de houle sur un maillage

Le simulateur a vocation à représenter le comportement de solides dans un
environnement fluide, mais il peut aussi servir à simuler un environnement,
sans aucun solide. Ce peut être intéressant par exemple pour générer des champs
de vague afin de tester des algorithmes de prédiction de mouvement sur houle.
Ce tutoriel explique comment utiliser le simulateur pour ce type de simulation.

### Description du problème

Dans cet exemple, nous simulerons une houle d'Airy constituée de la somme de
deux spectres directionnels :

- l'un de densité spectrale JONSWAP et mono-directionnel
- l'autre monochromatique ayant une dispersion en cos2s

On suppose en outre avoir 100 m de fond.

On se limite dans cet exemple à deux spectres, mais le simulateur permet d'en
sommer autant qu'on le souhaite (on n'est limité que par la mémoire de la
machine et par le temps disponible).

### Écriture du fichier de configuration du simulateur

```python echo=False, results='raw', name='tutorial_03_load_yaml'
yaml_data = load_yaml('tutorial_03_waves.yml')
```

La section `environment models` est nettement plus fournie que pour les
tutoriels précédents.

On commence par définir la discrétisation. Actuellement, le nombre de
pulsations est égal au nombre de directions : il s'agit d'une limitation du code.

```python echo=False, results='raw', name='tutorial_03_print_wave_discretization'
print_yaml(yaml_data, 'environment models/0/discretization')
```

On va donc sommer <% yaml_data['environment models'][0]['discretization']['n'] %> pulsations et
<% yaml_data['environment models'][0]['discretization']['n'] %> directions,
soit <% yaml_data['environment models'][0]['discretization']['n']*yaml_data['environment models'][0]['discretization']['n'] %> points.
Cependant, la discrétisation spatiale des spectres monochromatiques et des
dispersions monodirectionnelles est réduite à un point.
On spécifie en outre
que l'on veut représenter
<%yaml_data['environment models'][0]['discretization']['energy fraction']*100 %> %
de l'énergie totale, les autres composantes n'étant pas retenues.

Le premier spectre est défini de la façon suivante :

```python echo=False, results='raw', name='tutorial_03_print_first_spectrum'
print_yaml(yaml_data, 'environment models/0/spectra/0')
```

Pour le second spectre, on écrit :

```python echo=False, results='raw', name='tutorial_03_print_second_spectrum'
print_yaml(yaml_data, 'environment models/0/spectra/1')
```

On définit les sorties de la façon suivante :

```python echo=False, results='raw', name='tutorial_03_print_outputs_section'
print_yaml(yaml_data, 'environment models/0/output')
```

En définitive, l'environnement est défini de la façon suivante :


```python echo=False, results='raw', name='tutorial_03_print_environment_yaml'
print_yaml(yaml_data, 'environment models')
```

Comme on ne simule pas de corps, le fichier d'entrée se réduit à :

```python echo=False, results='raw', name='tutorial_03_print_full_yaml'
print_yaml_file('tutorial_03_waves.yml')
```

### Lancement de la simulation

La simulation peut maintenant être lancée comme suit :

```python echo=False, results='raw', name='tutorial_03_launch_simulation'
execCommand('xdyn tutorial_03_waves.yml --dt 1 --tend 1 -w tutorial_03_results.h5')
```

Le fichier de résultat est ici `tutorial_03_results.h5`.

### Résultats

On obtient un fichier hdf5 qui peut être ouvert avec différents logiciels comme HDFView.
Dans le groupe "outputs", on trouve un groupe "waves" qui contient quatre jeux de données nommés t, x, y et z.

- t donne les pas de temps de la simulation
- x donne les coordonnées selon x des points où l'élévation est calculée. Chaque ligne correspond à un pas de temps.
- y donne les coordonnées selon y des points où l'élévation est calculée. Chaque ligne correspond à un pas de temps.
- z donne l'élévation aux points définis par x et y. Chaque tranche correspond à un pas de temps.

La description de ce fichier est faite [dans la documentation des fichiers YAML](#sorties).

On peut obtenir les élévations dans n'importe quel repère de xdyn (NED ou lié à un solide). Si le repère est lié à un solide on obtient des coordonnées x et y changeantes au cours du temps.
