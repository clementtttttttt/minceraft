#include "entity/pig.hpp"
#include "api.hpp"
#include <unordered_map>
#include "world.hpp"
#include <stack>
rect pig_tex[]{{0, 0, 32, 16},  {0, 16, 32, 16}
                 };
static int anim_count;
static rect center;
extern void *tex;
extern void *mob;
pig::pig(double x,double y): entity(x,y,1.8,0.9)
{

    //ctor
}
extern int scrnw, scrnh;




// Define a structure to represent a node in the graph
struct Node
{
    vec2 pos; // Coordinates of the node in the graph
    int f, g; // Values used by the A* algorithm

    Node(double r, double c);
    Node(){

    }

    // Overload comparison operators for priority queue
    bool operator>(const Node& other) const;
    bool operator==(const Node& other) const;
    bool operator<(const Node& other) const;


};
template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
template <>
struct std::hash<Node>
{

  std::size_t operator()(const Node& k) const
  {

    using std::size_t;
    using std::hash;
    using std::string;
    size_t h= 0;
    hash_combine(h, k.pos.x);
    hash_combine(h, k.pos.y);
    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return h;//((hash<double>()(k.pos.x)
             //^ (hash<double>()(k.pos.y) << 1)) >> 1);
             //^ (hash<int>()(k.third) << 1);
  }
};

Node::Node(double _x, double _y)
: pos(_x,_y)
, f(INT_MAX)
, g(INT_MAX)
{
}

bool Node::operator<(const Node& other) const
{
    return f < other.f;
}

bool Node::operator>(const Node& other) const
{
    return f > other.f;
}

bool Node::operator==(const Node& other) const
{
    return (truncf(pos.x) == truncf(other.pos.x)) && (truncf(pos.y) == truncf(other.pos.y));
}


bool pig::is_valid_walking_target(){

    if(walk_target.x == 0){
        return false;
    }
    if((walk_target.y - y) > 1.2){
        return false;
    }
    if(getBlockType(walk_target.x, walk_target.y).bitfield & (0b1000000)){
        return false;
    }
    return true;
}
void pig::tick(){
    entity::tick();
    vec2 target = entity_list[0]->getpos();
    Node target_node = Node(entity_list[0]->getpos().x,entity_list[0]->getpos().y);
    std::    priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;



    const int directionX[] = {-1, -1,-1,0,0,1,1,1};
    const int directionY[] = {-1,0,1,-1,1,-1,0,1};

    if(!(truncf(old_target_pos.x) == truncf(target_node.pos.x)  || truncf(old_target_pos.y) == truncf(target_node.pos.y) )&& abs(entity_list[0]->get_momentum().x) <= 0.1 && abs(this->xmomentum) <= 0.1
        && this->onground
    ){

    std::unordered_map<Node,Node> cameFrom;
    std::cout << "PATHING" << std::endl;
    pathing_queue = std::queue<vec2>();
    Node start = Node(truncf(this->x),truncf(this->y));
    start.g = 0;
    start.f = target_node.pos.distance(start.pos);
    openList.push(start);
    while(!openList.empty()){

        Node current = openList.top();
        if(current == target_node){

            std::stack<vec2> rev_stack;
            while(!(current == start)){
            //    std::cout << it->pos.x << " " <<it->pos.y << std::endl;
                rev_stack.push(current.pos);
                current = cameFrom[current];
                std::cout << current.pos.x << " " << current.pos.y << std::endl;
            }

            while(!rev_stack.empty()){
                pathing_queue.push(rev_stack.top());
                rev_stack.pop();
            }
            std::cout << "REPORT END" << std::endl;
            break;
        }

        openList.pop();
        // Explore neighbors
        for (int i = 0; i < 8; ++i)
        {
            double newX = current.pos.x + directionX[i];
            double newY = current.pos.y + directionY[i];
            // Check if the neighbor is withi n the grid boundaries
           /* if (newX >= 0 && newX < graph.size() && newY >= 0 && newY < grid[0].size())
            {
                // Check if the neighbor is walkable and not in the closed list
                if (graph[newX][newY] == 0 && !closedList[newX][newY])
                {
                    Node neighbor(newX, newY);
                    int newG = current.g + 1;

                    // Check if the neighbor is not in the open list or has a lower g value
                    if (newG < neighbor.g || !closedList[newX][newY])
                    {
                        neighbor.g = newG;
                        neighbor.h = abs(newX - goal.x) + abs(newY - goal.y);
                        neighbor.f = neighbor.g + neighbor.h;
                        graph[newX][newY] = current; // Update the parent of the neighbor
                        openList.push(neighbor); // Add the neighbor to the open list
                    }
                }
            }*/
                                                Node neighbor(newX, newY);

            if( !(blockreg[getBlock(newX,newY).type].bitfield & (0b1000000)) && !(blockreg[getBlock(newX+1,newY).type].bitfield & (0b1000000)) && !(cameFrom.find(neighbor) != cameFrom.end())
                && neighbor.pos.distance(start.pos) <= 20
            ){
                    double newG = current.g + directionY[i]+1;

                    // Check if the neighbor is not in the open list or has a lower g value
                    if (newG < neighbor.g)
                    {

                        neighbor.g = newG;
                        int h =  abs(newX - target_node.pos.x) + abs(newY - target_node.pos.y);
                        neighbor.f = neighbor.g + h;

                        cameFrom[neighbor] = current;

                        openList.push(neighbor); // Add the neighbor to the open list

                    }
            }
        }

    }
                old_target_pos = target_node.pos;

    }
    if(!pathing_queue.empty()  && ((truncf(this->x) == truncf(walk_target.x)) || !is_valid_walking_target())){
               walk_target = vec2(pathing_queue.front());
        pathing_queue.pop();



    }

    else if(!pathing_queue.empty() ){
       if(walk_target.x>this->x){
            setmomentum(0.1,0);
        }
        else{
            setmomentum(-0.1,0);
        }
        if(walk_target.y > this->y && this->onground){
            setmomentum(0,0.6);
        }

        //this->aa
    }




}

void pig::rentick(){

  center.w = pig_tex[0].w * 4;
  center.h = pig_tex[0].h * 4;
  int scrnw, scrnh;
  sysspec_getscreensz(&scrnw,&scrnh);
    double blockcorner_x = (entity_list[0]->getpos().x) - (scrnw / 2 / 64);
  double blockcorner_y = (entity_list[0]->getpos().y) - (scrnh / 2 / 64) ;
  ;
  //            putblocc((*world_ref2)[absposx][posy].type,x * 64 - (scrnoffx * 64), scrnh - (y * 64 + scrnoffy * 64),64);

  center.x = (this->x- blockcorner_x) * 64 ;
  center.y =  scrnh - ((this->y - blockcorner_y )* 64 + (scrnh%128));
  sysspec_putimg(mob, &pig_tex[anim_count], &center);

}

int pig::gettype(){
    return ENTITY_PIG;
}

pig::~pig()
{
    //dtor
}
