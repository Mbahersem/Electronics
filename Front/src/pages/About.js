import React, {  useRef } from 'react';
import Header from '../components/Header';
import '../styles/pages/about.css'

function About() {

    var drop_one = useRef()
    var drop_two = useRef()
    var drop_three = useRef()
    var drop_four = useRef()

    return (

        <div className="about">
            <Header />

            <div className='doc-container'>

                <h1>Documentation pour les différentes semences</h1>

                <div className='doc-grid-container'>

                    <div className='doc-grid-elt one' onClick={() => { drop_one.current.classList.toggle('active') }} >

                        <div className='title'>
                            <img src='https://cdn-icons-png.flaticon.com/128/6120/6120696.png' alt='maize' />
                            <h2>Maïs</h2>
                        </div>

                        <div className='doc-body' ref={drop_one}>
                            <p>La croissance du maïs est influencée par différents facteurs,
                                notamment la disponibilité des nutriments, la température,
                                le pH et l'humidité. Voici quelques informations sur chacun
                                de ces facteurs (ceci est valable pour n'importe quelle variété de maïs ):
                            </p>
                            <p>
                                Nutriments (azote, phosphore et potassium) :
                            </p>
                            <p>
                                Le maïs nécessite généralement environ 0,34 à 0,57 kilogramme d'azote par 
                                mètre carré, environ 0,14 à 0,19 kilogramme de phosphore par mètre carré 
                                et aussi environ 0,41 à 0,54 kilogramme de potassium par mètre carré.
                            </p>
                            <p>
                                L'azote est important pour le développement des feuilles et des tiges, 
                                le phosphore favorise le développement des racines et la floraison, 
                                et le potassium contribue à la santé globale de la plante et à sa 
                                tolérance au stress.
                            </p>
                            <p>
                                Les besoins spécifiques en nutriments pour le maïs peuvent varier en 
                                fonction de facteurs tels que la fertilité du sol, la variété de la 
                                culture et le stade de croissance. Les tests et l'analyse du sol peuvent
                                 fournir des informations sur la teneur en nutriments et aider à 
                                 déterminer les stratégies de fertilisation appropriées. Les services
                                 de vulgarisation agricole locaux ou les institutions de recherche
                                 agricole peuvent fournir des directives spécifiques et des recommandations
                                 pour la gestion des nutriments dans la culture du maïs.
                            </p>
                            <p>
                                Température :
                            </p>
                            <p>
                                La température est un facteur important qui influence la croissance et
                                 le développement du maïs. Le maïs est une culture de saison chaude,
                                  et sa température de croissance optimale se situe généralement entre 
                                  20 et 30 degrés Celsius (68 à 86 degrés Fahrenheit). Les exigences 
                                  spécifiques en matière de température peuvent varier en fonction de la variété de maïs.
                                Le maïs nécessite des températures chaudes du sol pour la germination,
                                 avec un seuil minimum d'environ 10 degrés Celsius (50 degrés Fahrenheit).
                                  Des températures plus fraîches pendant les premiers stades de croissance
                                   peuvent entraîner une croissance réduite et un retard de maturité.
                            </p>
                            <p>
                                pH :
                            </p>
                            <p>
                                Le pH du sol affecte la disponibilité et l'absorption des nutriments par
                                 les plantes de maïs. Le pH optimal du sol pour la culture du maïs se 
                                 situe généralement entre 5,8 et 7,5. Cependant, le maïs peut tolérer 
                                 une plage de pH relativement large, en fonction des conditions spécifiques
                                  du sol. Il est essentiel d'évaluer et de gérer le pH du sol pour assurer
                                   une disponibilité optimale des nutriments et une absorption par les plantes
                                    de maïs. Les tests de sol et les techniques d'ajustement du pH, telles 
                                    que le chaulage ou l'acidification, peuvent aider à maintenir des niveaux
                                     de pH appropriés pour la croissance du maïs. 
                            </p>
                            <p>
                                Humidité :
                            </p>
                            <p>
                                Le maïs s'adapte généralement à un large éventail de conditions d'humidité.
                                 Cependant, des niveaux élevés d'humidité peuvent contribuer à une 
                                 pression accrue des maladies, telles que les infections fongiques, 
                                 notamment pendant les stades de reproduction. Un espacement adéquat 
                                 entre les plantes, une bonne circulation de l'air et de bonnes pratiques 
                                 de gestion des maladies peuvent aider à atténuer l'impact de l'humidité 
                                 élevée sur les cultures de maïs.
                            </p>
                        </div>

                    </div>

                    <div className='doc-grid-elt twos' onClick={() => { drop_two.current.classList.toggle('active') }}>

                        <div className='title'>
                            <img src='https://cdn-icons-png.flaticon.com/128/1686/1686965.png' alt='bean' />
                            <h2>Haricots</h2>
                        </div>

                        <div className='doc-body' ref={drop_two}>

                            <p>Les besoins en éléments nutritifs, les préférences de température, 
                                la plage de pH et les conditions d'humidité pour la croissance
                                 des haricots rouges, noirs , gros graine taché, gros graine
                                  rouge et blancs sont généralement similaires, car ils appartiennent
                                   à la même espèce végétale (Phaseolus vulgaris). Voici quelques 
                                   informations sur chacun de ces facteurs :
                            </p>
                            <p>
                                Besoins en éléments nutritifs :
                            </p>
                            <p>Les haricots, y compris les variétés rouges, noires et blanches, 
                                ont besoin d'éléments nutritifs essentiels pour leur croissance 
                                et leur développement. Les principaux macronutriments nécessaires 
                                aux haricots sont l'azote (N), le phosphore (P) et le potassium (K).
                                 Cependant, les besoins spécifiques en éléments nutritifs peuvent
                                  varier en fonction de facteurs tels que la fertilité du sol, la
                                   variété de la culture et le stade de croissance.
                            </p>
                            <p>En tant que ligne directrice générale, les haricots ont généralement
                                 besoin des quantités d'éléments nutritifs suivantes par hectare 
                                 ou mètre carré :
                            </p>

                            <p>
                                Azote (N) : 80 à 120 kilogrammes par hectare ou environ 3 à 5 kilogrammes
                                 d'azote par mètre carré.
                            </p>
                            <p>
                                Phosphore (P) : 40 à 60 kilogrammes par hectare ou environ 1 à 1,5 kilogramme
                                 de phosphore par mètre carré.
                            </p>
                            <p>
                                Potassium (K) : 80 à 120 kilogrammes par hectare ou environ 2 à 3 kilogrammes
                                 de potassium par mètre carré.
                            </p>
                            <p>
                                Il s'agit de valeurs approximatives, et il est recommandé de réaliser des 
                                tests de sol et de consulter des experts agricoles locaux pour obtenir des 
                                recommandations précises en matière d'éléments nutritifs en fonction de vos 
                                conditions spécifiques.
                            </p>

                            <p>
                                Température :
                            </p>
                            <p>
                                Les haricots sont des cultures de saison chaude qui préfèrent des températures 
                                modérées. La plage de température optimale pour la croissance des haricots, y 
                                compris les variétés rouges, noires et blanches, se situe généralement entre 20
                                 et 25 degrés Celsius (68 à 77 degrés Fahrenheit). Cependant, ils peuvent tolérer
                                  des températures allant de 15 à 30 degrés Celsius (59 à 86 degrés Fahrenheit).
                            </p>
                            <p>
                                Il est important de noter que les haricots sont sensibles au gel, il est donc 
                                préférable de les éviter lorsque le risque de gel est présent.
                            </p>

                            <p>
                                pH :
                            </p>
                            <p>
                                Les haricots préfèrent généralement des conditions de pH légèrement acides à
                                 neutres. La plage de pH optimale du sol pour la culture des haricots est d'environ
                                  6,0 à 7,0. Cependant, les haricots peuvent tolérer une plage de pH légèrement plus
                                   large, de 5,5 à 7,5.
                            </p>
                            <p>
                                Le pH du sol affecte significativement la disponibilité des éléments nutritifs pour
                                 les haricots. La réalisation d'un test de sol est essentielle pour déterminer le
                                  niveau de pH de votre sol et effectuer les ajustements appropriés si nécessaire.
                            </p>

                            <p>Humidité :</p>
                            <p>
                                Les haricots préfèrent généralement des niveaux d'humidité modérés pour une croissance
                                 optimale. Une humidité excessive peut augmenter le risque de maladies fongiques.
                                  Une bonne circulation de l'air et un espacement adéquat entre les plantes peuvent
                                   aider à réduire les problèmes liés à l'humidité.
                            </p>
                            <p>
                                Les haricots, y compris les variétés rouges, noires et blanches, peuvent tolérer
                                 une large gamme de conditions d'humidité. Cependant, il est préférable d'éviter les
                                  périodes prolongées d'humidité élevée, notamment pendant les stades de floraison et
                                   de développement des gousses.
                            </p>
                            <p>
                                Il est important de prendre en compte que les conditions locales spécifiques, telles
                                 que le climat, le type de sol et la variété, peuvent influencer les besoins précis
                                  des haricots rouges, noirs et blancs. Par conséquent, il est recommandé de consulter
                                   des experts agricoles locaux, des services de vulgarisation ou des lignes directrices
                                    de production de haricots spécifiques à votre région pour obtenir des recommandations
                                     plus précises et adaptées.
                            </p>

                        </div>

                    </div>

                    <div className='doc-grid-elt three' onClick={() => { drop_three.current.classList.toggle('active') }} >

                        <div className='title'>
                            <img src='https://cdn-icons-png.flaticon.com/128/3109/3109780.png' alt='rice' />
                            <h2>Riz</h2>
                        </div>

                        <div className='doc-body' ref={drop_three}>

                            <p>
                                Azote (N) : L'azote est un élément clé pour la croissance du riz, car il 
                                favorise le développement des feuilles et des tiges. Les recommandations 
                                générales pour la culture du riz sont d'appliquer environ 100 à 150 
                                kilogrammes d'azote par hectare. Cependant, les besoins en azote peuvent 
                                varier en fonction du type de sol, de la variété de riz et des pratiques 
                                agricoles spécifiques. Un apport équilibré en azote est essentiel pour 
                                obtenir de bons rendements et une qualité optimale du grain.
                            </p>
                            <p>
                                Phosphore (P) : Le phosphore est important pour la croissance des racines, 
                                la floraison et la formation des grains chez le riz. Les recommandations 
                                générales pour la culture du riz sont d'appliquer environ 40 à 60 
                                kilogrammes de phosphore par hectare. Cependant, les besoins en phosphore 
                                peuvent varier en fonction des conditions spécifiques du sol et des 
                                pratiques culturales. Un apport adéquat en phosphore favorise le développement 
                                des racines et la production de grains.
                            </p>
                            <p>
                                Potassium (K) : Le potassium est essentiel pour la vigueur globale des plantes, 
                                la résistance aux maladies et la qualité des grains chez le riz. Les 
                                recommandations générales pour la culture du riz sont d'appliquer environ 
                                80 à 120 kilogrammes de potassium par hectare. Cependant, les besoins en 
                                potassium peuvent varier en fonction du sol et des pratiques agricoles spécifiques. 
                                Un apport suffisant en potassium favorise une croissance vigoureuse des plantes 
                                et une meilleure résistance aux stress environnementaux.
                            </p>
                            <p>
                                Température : Le riz est une culture adaptée aux climats chauds et humides. 
                                Les températures optimales pour la croissance du riz se situent généralement 
                                entre 20 et 35 degrés Celsius. Des températures inférieures à 15 degrés Celsius 
                                peuvent ralentir la croissance du riz, tandis que des températures supérieures à 
                                35 degrés Celsius peuvent entraîner un stress thermique. Il est important de 
                                planifier la culture du riz en fonction des conditions de température de votre région.
                            </p>
                            <p>
                                pH du sol : Le riz préfère un pH du sol légèrement acide à neutre, généralement 
                                compris entre 6,0 et 7,5. Un pH du sol en dehors de cette plage peut affecter 
                                l'absorption des nutriments par les plantes. Il est recommandé de tester le 
                                pH du sol et d'apporter les ajustements nécessaires en utilisant des amendements 
                                appropriés avant la plantation du riz.
                            </p>
                            <p>
                                Humidité : Le riz est une culture semi-aquatique qui nécessite une quantité 
                                adéquate d'eau pour sa croissance. Pendant la période de croissance, le niveau 
                                de l'eau doit être régulé pour assurer une irrigation adéquate. Le riz nécessite 
                                généralement une disponibilité régulière d'eau pour maintenir le sol humide, 
                                mais il est important d'éviter une stagnation excessive de l'eau, ce qui peut 
                                entraîner des problèmes de pourriture des racines. Une gestion appropriée de 
                                l'eau est essentielle pour la réussite de la culture du riz.
                            </p>

                        </div>

                    </div>

                    <div className='doc-grid-elt four' onClick={() => { drop_four.current.classList.toggle('active') }} >

                        <div className='title'>
                            <img src='https://cdn-icons-png.flaticon.com/128/9849/9849878.png' alt='peanuts' />
                            <h2>Arachides</h2>
                        </div>

                        <div className='doc-body' ref={drop_four}>

                            <p>
                                Les paramètres recommandés pour la culture de l'arachide en ce qui 
                                concerne les éléments nutritifs, le pH, la température et l'humidité 
                                peuvent varier en fonction des conditions locales, des pratiques 
                                agricoles et des variétés cultivées. Cependant, voici des informations 
                                générales sur ces paramètres
                            </p>
                            <p>
                                Éléments nutritifs :
                            </p>
                            <p>
                                Azote (N) : L'arachide a généralement besoin d'une quantité adéquate 
                                d'azote pour sa croissance et son développement. Les besoins en azote 
                                peuvent varier, mais une recommandation générale est d'appliquer 
                                environ 60 à 90 kg d'azote par hectare.
                            </p>
                            <p>
                                Phosphore (P) : Le phosphore est essentiel pour la formation et le 
                                développement des racines de l'arachide. L'application de phosphore 
                                dépend des niveaux de phosphore dans le sol, mais une recommandation 
                                générale est d'appliquer environ 30 à 60 kg de phosphore par hectare.
                            </p>
                            <p>
                                Potassium (K) : Le potassium est important pour la résistance aux 
                                maladies, la formation des gousses et la qualité globale de l'arachide. 
                                Les besoins en potassium peuvent varier, mais une recommandation 
                                générale est d'appliquer environ 60 à 90 kg de potassium par hectare.
                            </p>
                            <p>
                                Il est important de réaliser une analyse du sol pour déterminer les 
                                niveaux spécifiques de ces éléments nutritifs et ajuster les quantités 
                                d'engrais en conséquence.
                            </p>
                            <p>
                                Température : L'arachide est une culture sensible à la température. 
                                Elle nécessite des températures chaudes pour une croissance optimale. 
                                La température idéale pour la culture de l'arachide se situe généralement 
                                entre 25°C et 35°C pendant la journée. Des températures inférieures à 
                                15°C ou supérieures à 40°C peuvent avoir un impact négatif sur la croissance 
                                et le rendement de l'arachide.
                            </p>
                            <p>
                                pH du sol : L'arachide prospère généralement dans un sol légèrement acide à 
                                neutre, avec un pH compris entre 6,0 et 7,5. Un pH du sol en dehors de cette 
                                plage peut affecter l'absorption des nutriments par la plante. Si le pH est 
                                trop bas (acide), il peut être nécessaire d'ajuster le pH du sol en ajoutant 
                                des amendements calcaires.
                            </p>
                            <p>
                                Humidité : L'arachide nécessite une quantité adéquate d'eau pour une croissance 
                                optimale. Les besoins en eau peuvent varier en fonction du stade de croissance 
                                de la plante et des conditions climatiques locales. Cependant, en général, 
                                l'arachide a besoin d'un approvisionnement régulier en eau pendant sa période 
                                de croissance. Une irrigation appropriée est souvent nécessaire, en particulier 
                                pendant les périodes sèches.
                            </p>

                        </div>

                    </div>

                </div>

            </div>

        </div>

    );

};

export default About;