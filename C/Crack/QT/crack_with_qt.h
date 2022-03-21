#pragma once
 
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class QProgressBar;

class PlusMinus : public QWidget {

	Q_OBJECT // этот макрос должен включаться в классы, которые объявляют свои собственные сигналы и слоты

	public:
		PlusMinus(QWidget *parent = 0);

	private slots:
		void OnPlus();
		void updateProgress();

	private:
		QLabel *lbl;
		QLabel *l;
		QProgressBar *progressBar;
		QGridLayout *grid;
};