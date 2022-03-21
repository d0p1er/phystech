#include <QGridLayout>
#include <QProgressBar>
#include <QLayout>
#include <QTimer>

#include "crack_with_qt.h"

PlusMinus::PlusMinus(QWidget *parent) : QWidget(parent) {
	QPushButton *plsBtn = new QPushButton("ВЗЛОМАТЬ ЖОПУ МАКСА?", this);
	lbl = new QLabel("ASS ASS ASS ASS ASS ASS ASS ASS ASS ASS", this);

	grid = new QGridLayout(this);
	plsBtn->setStyleSheet("color:red;");
	grid->addWidget(plsBtn, 0, 0);
	grid->addWidget(lbl, 1, 0);

	setLayout(grid);  

	progressBar = new QProgressBar();
	progressBar->setMinimum(0);
	progressBar->setMaximum(20);

	printf("%d\n", progressBar->value());

	grid->addWidget(progressBar);


	connect(plsBtn, &QPushButton::clicked, this, &PlusMinus::OnPlus);
}


void PlusMinus::OnPlus() {
	lbl->setText("ДЛЯ УСКОРЕНИЯ ПОТЫКАЙ НА КНОПКУ");

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &PlusMinus::updateProgress);
	timer->start(1000);
}


void PlusMinus::updateProgress() {
	progressBar->setValue(progressBar->value()+1);

	if (progressBar->value() >= 20) {
		l = new QLabel("ЖОПА ВЗЛОМАНА", this);
		l->setStyleSheet("color:red;");
		grid->addWidget(l, 2, 0);
	}
}