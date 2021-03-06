/*
 * Xournal++
 *
 * A page position (a vertical rect)
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __PAGEPOSITION_H__
#define __PAGEPOSITION_H__

#include <glib.h>
#include <XournalType.h>

class PageView;

/**
 * @brief A set of PageView%s within an interval of y coordinates
 */
class PagePosition
{
public:
	PagePosition();
	PagePosition(PageView* pv);
	virtual ~PagePosition();

public:
	/**
	 * Adds a PageView to this PagePosition provided that the
	 * y interval is not split up
	 * 
	 * @return whether or not the PageView was added
	 */
	bool add(PageView* pv);

	/**
	 * Returns whether or not the given y value is in
	 * the current interval
	 */
	bool containsY(int y) const;

	/**
	 * Returns whether the given y value is below the
	 * current interval
	 */
	bool isYSmallerThan(int y) const;

	/**
	 * Returns whether the given y value is above the
	 * current interval
	 */
	bool isYGraterThan(int y) const;

	/**
	 * Returns the PageView containing the given
	 * point display point
	 */
	PageView* getViewAt(int x, int y);

private:
	XOJ_TYPE_ATTRIB;

	// the minimal/maximal y coordinates
	int y1;
	int y2;

	// a list of PageViews 
	GList* views;

	friend class PagePositionHandler;
};

#endif /* __PAGEPOSITION_H__ */
