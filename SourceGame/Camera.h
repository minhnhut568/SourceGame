#pragma once
#include"MovableRect.h"
#include"Space.h"
/* camera là 1 hình chữ nhật có thể di chuyển nên sẽ kế thừa lại lớp MovableRect */
class Camera : public MovableRect
{
	static Camera* instance;

	Space* space;
	
public:
	static Camera* getInstance();
	/* phương thức chuyển đổi world qua view
		Tham số đầu vào là xWorld yWorld
		Tham số cần lấy là xView yView (nên có dấu &, cần xem lại khái niệm về tham chiếu C++ để hiểu)
		Phương thức này trong sách game có giở sách ra xem sẽ thấy
	*/
	void convertWorldToView(float xWorld, float yWorld, float& xView, float& yView);
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;

	void setSpace(Space* space);

	/* cập nhật camera */
	void update();

	Camera();
	~Camera();
};

