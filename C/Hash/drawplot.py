import matplotlib.pyplot as plt

input_data = 'Data/output{}'
amount_plots = 6


def LoadData():
	list_of_data = []
	for i in range(amount_plots):
		with open(input_data.format(i)) as f:
			list_of_data.append([list(map(int, line.split())) for line in f])

	return list_of_data


def ShowPlots(list_of_data):
	params = {'text.color' : 'white', 'xtick.color' : 'white', 'ytick.color' : 'white', 'figure.facecolor' : '#282930', 'axes.facecolor' : '#3e3e3e'} 
	plt.rcParams.update(params)
	fig, axs = plt.subplots(2, 3, figsize = (12, 10))

	for i in range(amount_plots):
		axs[i//3][i%3].scatter(list_of_data[i][0], list_of_data[i][1], s = 2, color = '#ff80ff')

	# axs[1][1].set_xlim(550, 750)
	# axs[1][1].set_ylim(0, 20)

	plt.show()


ShowPlots(LoadData())
