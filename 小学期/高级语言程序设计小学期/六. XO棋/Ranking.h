#pragma once
class Ranking {
	//ÓÃÀ´ÅÐ¶Ï
public:
	Ranking(int c = 0, int r = 0, int l = 0, int i = 0) {
		this->_col = c;
		this->_row = r;
		if (i) {
			_weight = 10 * l + 5;
		} else {
			_weight = 10 * l;
		}
	}

	bool operator<(Ranking r) {
		return this->_weight > r._weight;
	}

	bool operator==(Ranking r) {
		if (this->_col == r._col)
			if(this->_row == r._row)
				if(this->_weight == r._weight)
					return 1;
		return 0;
	}

	bool operator!=(Ranking r) {
		if (this->_weight != r._weight) return 1;
		return 0;
	}

	int getCol() { return this->_col; }
	int getRow() { return this->_row; }
	int getWei() { return this->_weight; }
private:
	int _col;
	int _row;
	int _weight;
};
