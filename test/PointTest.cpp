#include <vector>

#include "gtest/gtest.h"

#include "Point.h"

using namespace std;

#define checkPointsEqual(a, b) \
    EXPECT_EQ((a).x, (b).x); \
    EXPECT_EQ((a).y, (b).y)

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

void check6NearestPoints(const Point &center, const vector<Point> &points) {
	{
		auto nearest = nearestPoints(center, points, points.size() - 1);
		EXPECT_EQ(points.size() - 1, nearest.size());
		vector<Point> expected{
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}

	{
		auto nearest = nearestPoints(center, points, points.size() - 2);
		EXPECT_EQ(points.size() - 2, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}

	{
		auto nearest = nearestPoints(center, points, points.size() - 3);
		EXPECT_EQ(points.size() - 3, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}

	{
		auto nearest = nearestPoints(center, points, 2);
		EXPECT_EQ(2, nearest.size());
		vector<Point> expected{
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}

	{
		auto nearest = nearestPoints(center, points, 1);
		EXPECT_EQ(1, nearest.size());
		vector<Point> expected{
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
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

	check6NearestPoints(center, points);
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

	check6NearestPoints(center, points);
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

	check6NearestPoints(center, points);
}

TEST(NearestElements, MorePoints) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 0, .y = 4},
		Point{.x = 5, .y = 0},
		Point{.x = 6, .y = 0},
		Point{.x = 1, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 8},
		Point{.x = 7, .y = 0},
		Point{.x = 2, .y = 8},
		Point{.x = 0, .y = 9},
		Point{.x = 1, .y = 9},
	};

	{
		auto nearest = nearestPoints(center, points, 7);
		EXPECT_EQ(7, nearest.size());
		vector<Point> expected{
			Point{.x = 7, .y = 0},
			Point{.x = 6, .y = 0},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 8);
		EXPECT_EQ(8, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 8},
			Point{.x = 7, .y = 0},
			Point{.x = 6, .y = 0},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 9);
		EXPECT_EQ(9, nearest.size());
		vector<Point> expected{
			Point{.x = 2, .y = 8},
			Point{.x = 0, .y = 8},
			Point{.x = 7, .y = 0},
			Point{.x = 6, .y = 0},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 10);
		EXPECT_EQ(10, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 9},
			Point{.x = 2, .y = 8},
			Point{.x = 0, .y = 8},
			Point{.x = 7, .y = 0},
			Point{.x = 6, .y = 0},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
}

TEST(NearestElements, RepeatedPoints) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 1, .y = 0},
		Point{.x = 1, .y = 0},
		Point{.x = 6, .y = 0},
		Point{.x = 0, .y = 4},
		Point{.x = 5, .y = 0},
		Point{.x = 5, .y = 0},
	};

 	{
		auto nearest = nearestPoints(center, points, 7);
		EXPECT_EQ(7, nearest.size());
		vector<Point> expected{
			Point{.x = 5, .y = 0},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 6);
		EXPECT_EQ(6, nearest.size());
		vector<Point> expected{
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 5);
		EXPECT_EQ(5, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 1, .y = 0},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
}

/*
TEST(NearestElements, DistinctPointsSameDistance) {
	Point center{.x =  0, .y =  0};
	vector<Point> points{
		Point{.x = 2, .y = 0},
		Point{.x = 0, .y = 3},
		Point{.x = 1, .y = 0},
		Point{.x = 0, .y = 1},
		Point{.x = 6, .y = 0},
		Point{.x = 0, .y = 4},
		Point{.x = 0, .y = 5},
		Point{.x = 5, .y = 0},
	};

	{
		auto nearest = nearestPoints(center, points, 7);
		EXPECT_EQ(7, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 5},
			Point{.x = 5, .y = 0},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 0, .y = 1},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 6);
		EXPECT_EQ(6, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 5},
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 0, .y = 1},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
	{
		auto nearest = nearestPoints(center, points, 5);
		EXPECT_EQ(5, nearest.size());
		vector<Point> expected{
			Point{.x = 0, .y = 4},
			Point{.x = 0, .y = 3},
			Point{.x = 2, .y = 0},
			Point{.x = 0, .y = 1},
			Point{.x = 1, .y = 0},
		};
		for (auto i = 0; i < nearest.size(); ++i) {
			checkPointsEqual(expected[i], nearest[i]);
		}
	}
}
 */