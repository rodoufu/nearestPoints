#include <vector>

#include "gtest/gtest.h"
#include "Point.h"

using namespace std;

const vector<Point> &printVec(const vector<Point> &points) {
	puts("{");
	for (auto &x : points) {
		printf("{x: %lf, y:%lf},\n", x.x, x.y);
	}
	puts("}");

	return points;
}

void checkPointsEqual(const Point &a, const Point &b) {
	EXPECT_EQ(a.x, b.x);
	EXPECT_EQ(a.y, b.y);
}

TEST(NearestElements, NoElements) {
	Point center{.x =  0, .y =  0};
	vector<Point> points;

	EXPECT_EQ(0, nearestPoints(center, points, 0).size());
	EXPECT_EQ(0, nearestPoints(center, points, 1).size());
	EXPECT_EQ(0, nearestPoints(center, points, 2).size());
}

TEST(NearestElements, NlargerThanNumberOfElements) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 1, .y = 0},
	};

	EXPECT_EQ(points.size(), nearestPoints(center, points, points.size()).size());
	EXPECT_EQ(points.size(), nearestPoints(center, points, points.size() + 1).size());
	EXPECT_EQ(points.size(), nearestPoints(center, points, points.size() + 2).size());
	EXPECT_EQ(points.size(), nearestPoints(center, points, points.size() + 3).size());
}

TEST(NearestElements, NsmallerThanNumberOfElements) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 1, .y = 0},
		Point{.x = 6, .y = 0},
		Point{.x = 0, .y = 4},
		Point{.x = 5, .y = 0},
	};

	{
		auto nearestN4 = nearestPoints(center, points, points.size() - 1);
		EXPECT_EQ(points.size() - 1, nearestN4.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN4.size(); ++i) {
			checkPointsEqual(expected[i], nearestN4[i]);
		}
	}

	{
		auto nearestN3 = nearestPoints(center, points, points.size() - 2);
		EXPECT_EQ(points.size() - 2, nearestN3.size());
		vector<Point> expected{
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN3.size(); ++i) {
			checkPointsEqual(expected[i], nearestN3[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, points.size() - 3);
		EXPECT_EQ(points.size() - 3, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 2);
		EXPECT_EQ(2, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 1);
		EXPECT_EQ(1, nearestN2.size());
		vector<Point> expected{
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}
}

TEST(NearestElements, PointsInAscendingOrder) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 1, .y = 0},
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 0, .y = 4},
		Point{.x = 5, .y = 0},
		Point{.x = 6, .y = 0},
	};

	{
		auto nearestN4 = nearestPoints(center, points, points.size() - 1);
		EXPECT_EQ(points.size() - 1, nearestN4.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN4.size(); ++i) {
			checkPointsEqual(expected[i], nearestN4[i]);
		}
	}

	{
		auto nearestN3 = nearestPoints(center, points, points.size() - 2);
		EXPECT_EQ(points.size() - 2, nearestN3.size());
		vector<Point> expected{
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN3.size(); ++i) {
			checkPointsEqual(expected[i], nearestN3[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, points.size() - 3);
		EXPECT_EQ(points.size() - 3, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 2);
		EXPECT_EQ(2, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 1);
		EXPECT_EQ(1, nearestN2.size());
		vector<Point> expected{
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}
}

TEST(NearestElements, PointsInDescendingOrder) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 6, .y = 0},
		Point{.x = 5, .y = 0},
		Point{.x = 0, .y = 4},
		Point{.x = 0, .y = 3},
		Point{.x = 2, .y = 0},
		Point{.x = 1, .y = 0},
	};

	{
		auto nearestN4 = nearestPoints(center, points, points.size() - 1);
		EXPECT_EQ(points.size() - 1, nearestN4.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN4.size(); ++i) {
			checkPointsEqual(expected[i], nearestN4[i]);
		}
	}

	{
		auto nearestN3 = nearestPoints(center, points, points.size() - 2);
		EXPECT_EQ(points.size() - 2, nearestN3.size());
		vector<Point> expected{
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN3.size(); ++i) {
			checkPointsEqual(expected[i], nearestN3[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, points.size() - 3);
		EXPECT_EQ(points.size() - 3, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 2);
		EXPECT_EQ(2, nearestN2.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}

	{
		auto nearestN2 = nearestPoints(center, points, 1);
		EXPECT_EQ(1, nearestN2.size());
		vector<Point> expected{
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearestN2.size(); ++i) {
			checkPointsEqual(expected[i], nearestN2[i]);
		}
	}
}
