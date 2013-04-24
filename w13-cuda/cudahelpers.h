#include <GL/gl.h>
class MyCUDAWrapper{
 

	public:
	MyCUDAWrapper();
	~MyCUDAWrapper(){};

	void init();
	void connect(GLuint buffID, int size);
	void disconnect();
	void run(float a, float b);
	
	private:
	struct cudaGraphicsResource* m_pbo_CUDA;
  int m_size;

};

