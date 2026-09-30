//$(document).ready(function() {
window.addEventListener("DOMContentLoaded", (event) => {
	const myChart = new Chart(document.getElementById('myChart'), config);	
});

//var size = 33; // nombre d'éléments sur l'axe des abscisses

// Génération du graphique
labels = new Array(size); // tableau qui contiendra les valeurs en abscisse
	
var data = { // les données du graphique
	labels: labels,                // les étiquettes en abscisse
	datasets: [{                   // données représentées par le graphique (3 courbes)
		label: 'Physique',         // légende de la courbe 1
		backgroundColor: 'green', 
		borderColor: 'green',
		data: [],				   // données de la courbe 1
		tension: 0.25			   // lissage de la courbe (tension de la courbe de Bézier, 0 pour une ligne droite)
	},
	{
		label: 'Emotionnel',	   // légende de la courbe 2
		backgroundColor: 'red',
		borderColor: 'red',
		data: [],				   // données de la courbe 2
		tension: 0.25
	},
	{	
		label: 'Intellectuel',	   // légende de la courbe 3
		backgroundColor: '#00f7ff',
		borderColor: '#00f7ff',
		data: [],				   // données de la courbe 3
		tension: 0.25
	}]
};

// Données de différentes courbes (vides à ce stade)
data.datasets[0].data = new Array(size);
data.datasets[1].data = new Array(size);
data.datasets[2].data = new Array(size);

// les données sont alimentées par le cgi qui crée le fichier data
// dans lequel sont initialisés les size(33) éléments de
// • labels
//   labels[i] =
// • data.datasets[0].data
//   data.datasets[0].data[i] =
// • data.datasets[1].data
//   data.datasets[1].data[i] =
// • data.datasets[2].data
//   data.datasets[2].data[i] =

// Configuration
const config = {
	type: 'line',
	data: data,
	options: {
		scales: {
			x: {  // <-- axis is not array anymore, unlike before in v2.x: '[{'
				ticks: {
                    color: 'white'
                },
				grid: {
					color: 'white',
					borderColor: 'white'  // <-- this line is answer to initial question
      			},
    		},
			y: {  // <-- axis is not array anymore, unlike before in v2.x: '[{'
				ticks: {
                    color: 'white'
                },
				grid: {
					color: 'white',
					borderColor: 'white'  // <-- this line is answer to initial question
      			}
    		}
  		},
		plugins: {
            legend: {
                labels: {
                    color: 'white',
                    // This more specific font property overrides the global property
					font: {
                        size: 14
                    }
                }
            }
        }
    }
};
