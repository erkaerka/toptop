#include<raylib.h>
#include<math.h>
#include<raymath.h>
//define linked list
class circlelist {
	public :
		int n=0;
		int r=0;
		float w = 1;
		Vector2 pos={800,450};
		Color color=RED;
		circlelist* next=NULL;
		circlelist* prev=NULL;
};
//add new circle
void addend(circlelist** head,int n, int r ,float w,Color color){
	circlelist* newnode = new circlelist;
	newnode->n = n;
	newnode->r = r;
	newnode->w = w;
	newnode->color = color;
	if (*head == NULL) {
		newnode->prev = NULL;
		*head = newnode;
		return;
	};
	circlelist* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	};
	temp->next = newnode;
	newnode->prev = temp;
};
//delete last circle
void clear(circlelist** head) {
	circlelist* temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	};
	circlelist* aux = temp->prev;
	delete temp;
	aux->next = NULL;
};
//update all positions
void update(circlelist** head,float t){
	circlelist* curr = *head;
	while (curr->next != NULL)
	{
		curr = curr->next;
		Vector2 newpos = Vector2{ 50 * (float)cos(curr->w*curr->n * t), -50 * (float)sin(curr->w*curr->n * t) };
		curr->pos = Vector2Add((curr->prev)->pos, newpos);
	};
};
//return random color
Color randcolor() {
	switch (GetRandomValue(1,6))
	{
	case 1:
		return RED;
	case 2:
		return GREEN;
	case 3 :
		return BLUE;
	case 4:
		return YELLOW;
	case 5:
		return PINK;
	default:
		return ORANGE;
	} 
};
//set the angular velocities of all lines (relative to their circles) equal to 1
void sync(circlelist** head) {
	circlelist* curr = *head;
	while (curr->next!=NULL)
	{
		curr = curr->next;
		curr->w = 1;
	}
};

	int main() {
		const int w = 1600;
		const int h = 900;
		float  t = 0;
		float s = 0;
		//initialize linked list
		circlelist* head = new circlelist;
		head->pos = Vector2{ (float)w / 2,(float)h / 2 };
		head->color = randcolor();
		head->r = GetRandomValue(10, 20);
		//start loop
		InitWindow(w, h, "top");
		SetTargetFPS(60);
		while (!WindowShouldClose()) {
			//controls
			DrawText("LEFT CLICK=ADD", 5, 5, 20, BLACK);
			DrawText("RIGHT CLICK=REMOVE", 5, 30, 20, BLACK);
			DrawText("SPACE=SYNCHRONIZE", 5, 55, 20, BLACK);
			DrawText("UP=INCREASE SPEED", 5, 80, 20, BLACK);
			DrawText("DOWN=DECREASE SPEED/TIME TRAVEL LOL", 5, 105, 20, BLACK);
			DrawFPS(1520, 0);
			circlelist* curr = head;
			//add new circle on user command
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				
				while (curr->next != NULL)
				{
					curr = curr->next;
				};
				addend(&curr, (curr->n)+1 , GetRandomValue(10, 20),GetRandomValue(-5,5), randcolor());
			};
			//delete circle on user command
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) and curr->next != NULL)
			{
				clear(&curr);
				
			};
			//call sync func on user command
			if (IsKeyPressed(KEY_SPACE))
			{
				sync(&head);
			};
			//speed up on user command
			if (IsKeyPressed(KEY_UP))
			{
				s+=0.01;
			};
			//speed down on user command
			if (IsKeyPressed(KEY_DOWN))
			{
				s -= 0.01;
			};
			BeginDrawing();

			ClearBackground(GRAY);
			//draw circles and lines iterating through the linked list
			curr = head;
			while (curr->next != NULL)
			{
				
				DrawLineEx(curr->pos, (curr->next)->pos, 2, BLACK);
				DrawCircleV(curr->pos, curr->r, curr->color);
				curr = curr->next;
			};
			//update positions according to t
			t+=0.01+s;
			update(&head, t);

			EndDrawing();




		};
		CloseWindow();
		
	};