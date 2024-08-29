#include <Vk/VkApp.h>
#include <Vk/VkWindow.h> 
#include <Vk/VkNode.h> 
#include <Vk/VkGraph.h> 
#include <Vk/VkMenu.h>

// https://irix7.com/techpubs/007-2124-004.pdf

class GraphWindow: public VkWindow {
    public:
        GraphWindow(const char *); 
        ~GraphWindow();

        virtual const char* className();

    protected: 
        VkGraph *graph;
        VkNode *p_node, *c1_node, *c2_node, *gc1_node, *gc2_node;

    private: 
        static void quitCallback (Widget, XtPointer, XtPointer);
        static VkMenuDesc appMenuPane[];
};

VkMenuDesc GraphWindow::appMenuPan[] = {
    { ACTION, "Quit", &GraphWindow::quitCallback }, 
    {END}
};

GraphWindow::GraphWindow(const char *name) : VkWindow( name ) 
{
    // Create nodes

    p_node = new VkNode("parentNode", "Parent");
    c1_node = new VkNode("childNode1", "Child 1");
    c2_node = new VkNode("childNode2", "Child 2");
    gc1_node = new VkNode("grandChildNode1", "Grandchild 1");
    gc2_node = new VkNode("grandChildNode2", "Grandchild 2");

    // Create graph

    graph = new VkGraph( "graph", mainWindowWidget() );

    // Add nodes to graph

    graph->add(p_node, c1_node);    // p_node is parent to c1_node
    graph->add(p_node, c2_node);    // p_node is parent to c2_node
    graph->add(c1_node, gc1_node);  // c1_node is parent to gc1_node
    graph->add(c1_node, gc2_node);  // c1_node is parent to gc2_node
  
    graph->displayAll();    // Display all nodes in graph 
    graph->doLayout();      // Layout the graph

    addView(graph);         // Set graph to be window's view 
    addMenuPane("Application", appMenuPane);    // Create menu bar
} 

GraphWindow::~GraphWindow() 
{
    delete graph; 
    delete p_node; 
    delete c1_node; 
    delete c2_node; 
    delete gc1_node; 
    delete gc2_node;
}

const char* 
GraphWindow::className() 
{
    return "GraphWindow";
}

void 
GraphWindow::quitCallback ( Widget, XtPointer, XtPointer ) 
{
    theApplication->quitYourself();
}

void main(int argc, char **argv) 
{
    VkApp *myApp = new VkApp("GraphViewer", &argc, argv); 
    
    GraphWindow *graphWin = new GraphWindow("GraphViewer");

    graphWin->show();
    myApp->run(); 
}

typedef int (*VkNodeSortFunction)(VkNode*, VkNode*)

class VkNode 
{
    private:
        std::vector<VkNode*> _parents;
        std::vector<VkNode*> _children;

        char *_label;
        char *_name;

    public:
        // Node Constructor and Destructor
    
        VkNode(const char *name, const char *label = NULL);
        VkNode(const char *name, VkNode *parent, const char *label = NULL);

        // Node Utility Functions

        void sortChildren();

        static void setSortFunction(VkNodeSortFunction func);

        // Node Access Functions

        char *name() const;
    
        virtual char *label();

        int nParents() const;
        VkNode *parent(int index);
        VkNode *findParent(char *name);

        int nChildren() const;
        VkNode *child(int index) const;
        VkNode *findChild(char *name);

    protected:
        virtual void build(Widget parent);

};


typedef Boolean (*VkGraphFilterProc) (VkNode *);

typedef void (*VkGraphNodeProc) (VkNode *);


class VkGraph 
{
    // VkGraph Constructor and Destructor

    VkGraph(char *name, Widget parent);

    virtual int add(VkNode *node);
    virtual void add(VkNode *parent, VkNode *child, char *attribute = NULL);

    virtual void remove(VkNode *node, Boolean deleteNode = FALSE);

    virtual void displayAll();
    void clearAll();

    virtual void display(VkNode *child);
    virtual VkNode *display(char *name);

    virtual void undisplay(VkNode *node); 
    virtual void hideNode(VkNode *node);

    virtual void displayWithChildren(VkNode *node); 
    virtual VkNode *displayWithChildren(char *name);

    virtual void expandNode(VkNode *node);

    virtual void displayWithAllChildren(VkNode *node); 
    virtual VkNode *displayWithAllChildren(char *name);

    virtual void expandSubgraph(VkNode *node);

    virtual void hideAllChildren(VkNode *node);

    virtual void hideWithAllChildren(VkNode *node);

    virtual void displayWithParents(VkNode *node); 
    virtual VkNode *displayWithParents(char *name);

    virtual void displayWithAllParents(VkNode *node); 
    virtual VkNode *displayWithAllParents(char *name);

    virtual void hideParents(VkNode *node);

    virtual void displayParentsAndChildren(VkNode *node);
    virtual VkNode *displayParentsAndChildren(char *name);

    virtual void hideParentsAndChildren(VkNode *node);

    virtual void displayIf(VkGraphFilterProc func);

    // Laying Out the Graph

    void doLayout();

    void doSubtreeLayout(VkNode *node);

    void doSparseLayout();

    // Butterfly Graphs

    virtual void displayButterfly(VkNode *node);
    virtual VkNode *displayButterfly(char *name);

    virtual void setLayoutStyle(char type);

    // Displaying a Graph Overview

    void showOverview();
    void hideOverview();

    VkWindow *overviewWindow();

    // Graph Utility Functions

    virtual void setZoomOption(int index);

    void sortAll();

    virtual void forAllNodesDo(VkGraphNodeProc function);

    void makeNodeVisible(VkNode *node);

    void saveToFile();

    void setSize(int entries);

    // Graph Access Functions

    int numNodes();

    VkNode *find(char *name);

    Widget graphWidget();
    Widget workArea();
    Widget twinsButton();
    Widget relayButton();
    Widget reorientButton();
};
