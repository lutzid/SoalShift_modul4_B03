#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
char charList[95] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV\']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
char charPos[200];
static const char *dirpath = "/home/zidan/shift4";
char directoryYoutuber[] = "/YOUTUBER";
// static const char *newEkstensi = ".iz1";
void precompute();
void encrypt(char* name);
void decrypt(char* name);

int b[1001];
void kmpPreprocsess(char pattern[]) {
	int i = 0, j = -1;
	b[0] = -1;
	while(i < strlen(pattern)) {
		while(j >= 0 && pattern[i] != pattern[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
	return;
}

bool kmpSearch(char text[], char pattern[]) {
	int i = 0, j = 0;
	while(i < strlen(text)) {
		while(j >= 0 && text[i] != pattern[j]) {
			j = b[j];
		}
		i++; j++;
		if(j == strlen(pattern)) {
			j = b[j];
			return true;
		}
	}
	return false;
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
	char tempPath[1000];
	strcpy(tempPath, path);
	encrypt(tempPath);
	sprintf(fpath,"%s%s",dirpath,tempPath);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
  char tempPath[1000];
  strcpy(tempPath, path);
	encrypt(tempPath);
	if(strcmp(tempPath,"/") == 0)
	{
		strcpy(tempPath, dirpath);
		sprintf(fpath,"%s",tempPath);
	}
	else sprintf(fpath, "%s%s",dirpath,tempPath);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		char tempFname[1000];
		struct stat st;
	    char fname[1001], file[1001];
	    strcpy(fname, de->d_name);
	    sprintf(file, "%s/%s", fpath, fname);
	    struct stat filest;
	    stat(file, &filest);
	    struct passwd *username = getpwuid(filest.st_uid);
	    struct group  *groupname = getgrgid(filest.st_gid);

	    if(access(file, R_OK) == -1 && access(file, W_OK) == -1 && access(file, X_OK) == -1){
	      if((strcmp(username->pw_name, "chipset") == 0 || strcmp(username->pw_name, "ic_controller") == 0) 
	      	&& strcmp(groupname->gr_name, "rusak") == 0)
	      {
	      	char address[1001], backup[1001];
	      	strcpy(address, dirpath);
	      	strcpy(backup, "/filemiris.txt");
	      	encrypt(backup);
	      	strcat(address, backup);
	      	FILE *fi;
	      	fi = fopen(address, "a+");
	      	time_t t = time(NULL);
			struct tm tm = *localtime(&t);

			fprintf(fi, "%s %s %s %d-%d-%d %d:%d:%d\n", fname, username->pw_name, groupname->gr_name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	        remove(file);
	    	fclose(fi);
	      }
	    }
	   
		    memset(&st, 0, sizeof(st));
			st.st_ino = de->d_ino;
			st.st_mode = de->d_type << 12;
			strcpy(tempFname, de->d_name);
			decrypt(tempFname);
			res = (filler(buf, tempFname, &st, 0));
				if(res!=0) break;
	    
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
  char tempPath[1000];
  strcpy(tempPath, path);
  encrypt(tempPath);
	if(strcmp(tempPath,"/") == 0)
	{
		strcpy(tempPath, dirpath);
		sprintf(fpath,"%s",tempPath);
	}
	else sprintf(fpath, "%s%s",dirpath,tempPath);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];
	char tempPath[1000];
	strcpy(tempPath, path);
	encrypt(tempPath);
	if(strcmp(tempPath,"/") == 0)
	{
		strcpy(tempPath, dirpath);
		sprintf(fpath,"%s",tempPath);
	}
	else sprintf(fpath, "%s%s",dirpath,tempPath);
	if(kmpSearch(fpath, directoryYoutuber) == 1) {
		mode = 0750;
	}
	res = mkdir(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi) {

    (void) fi;
    int res;
	char fpath[1000];
	char tempPath[1000];
	char enciz[1000];
	strcpy(tempPath, path);
	encrypt(tempPath);
	strcpy(enciz, ".iz1");
	encrypt(enciz);
    if(kmpSearch(tempPath, directoryYoutuber) == 1) {
    	mode = 0640;
    	strcat(tempPath, enciz);
    }
	if(strcmp(tempPath,"/") == 0)
	{
		strcpy(tempPath, dirpath);
		sprintf(fpath,"%s",tempPath);
	}
	else {
		sprintf(fpath, "%s/%s",dirpath,tempPath);
	} 
    res = creat(fpath, mode);
    if(res == -1)
	return -errno;

    close(res);

    return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	struct timeval tv[2];
	int res;
	char fpath[1000];
	char tempPath[1000];
	strcpy(tempPath, path);
	encrypt(tempPath);
	// mode_t mode;
	if(strcmp(tempPath,"/") == 0)
	{
		strcpy(tempPath, dirpath);
		sprintf(fpath,"%s",tempPath);
	}
	else sprintf(fpath, "%s/%s",dirpath,tempPath);
	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;
	// if(kmpSearch(fpath, directoryYoutuber) == 1) {
		// strcat(fpath, ".iz1");
	// }
	res = utimes(fpath, tv);
	// res = chmod(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res;
	char enciz[1000];
	strcpy(enciz, ".iz1");
	encrypt(enciz);
	if(strstr(&path[strlen(path)-5], ".iz1") != NULL)
		perror("File ekstensi iz1 tidak boleh diubah permissionnya.");
	else{
		res = chmod(path, mode);
		if (res == -1)
			return -errno;
	}

	return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.mkdir 		= xmp_mkdir,
	.create 	= xmp_create,
	.utimens 	= xmp_utimens,
	.chmod 		= xmp_chmod,
};

int main(int argc, char *argv[])
{
	precompute();
	kmpPreprocsess(directoryYoutuber);
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}

void precompute() {
  int panjang = strlen(charList), i;
  for(i = 0; i < panjang; i++) {
    charPos[(int)charList[i]] = i;
  }
  return;
}
void encrypt(char* name) {
	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) return;
  int panjang = strlen(name), i;
  for(i = 0; i < panjang; i++) {
    if(name[i] == '/') {
      continue;
    }
    char huruf = name[i];
    int hurufPos = charPos[(int)huruf];
    hurufPos += 17;
    hurufPos %= 94;
    char hurufBaru = charList[hurufPos];
    name[i] = hurufBaru;
  }
  return;
}

void decrypt(char* name) {
	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) return;
  int panjang = strlen(name), i;
  for(i = 0; i < panjang; i++) {
    if(name[i] == '/') {
      continue;
    }
    char huruf = name[i];
    int hurufPos = charPos[(int)huruf];
    hurufPos -= 17;
    if(hurufPos < 0)
      hurufPos += 94;
    char hurufBaru = charList[hurufPos];
    name[i] = hurufBaru; 
  }
  return;
}