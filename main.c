/**
 * @description: dev�汾
 * @file: dev.c
 * @author: LiuKai
 * @ver: 4.0 2019/12/21
 */
#include "myhead.h"
#include "exception.h"

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 2.0 2019/12/21
 */
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int ID = 0; // ȫ�ֱ���IDΪÿһ���˵�Ψһ����
int colorCount = 0;
int main(int args, char *argv[])
{
    // colorTest
    /* PRINT_FONT_BLA
    printf("Hello world.\n");
    PRINT_FONT_BLU
    printf("Hello world.\n");
    PRINT_FONT_RED
    printf("Hello world.\n");
    PRINT_FONT_YEL
    printf("Hello world.\n");
    PRINT_FONT_GRE
    printf("Hello world.\n");
    PRINT_FONT_WHI
    printf("Hello world.\n");
    PRINT_FONT_PUR
    printf("Hello world.\n");
    PRINT_ATTR_REV
    printf("Hello world.\n");
    PRINT_ATTR_REC */

    char path[MAX_FILE_NAME];
    char strSel[MAX_FILE_NAME];
    char inputFileName[MAX_FILE_NAME] = "\0";  // �����ļ���
    char outputFileName[MAX_FILE_NAME] = "\0"; // ����ļ���
    bool fileExist = false;                    // �ļ��Ƿ���ڱ�־�� �ļ�����fileExistΪtrue
    int indexSel;                              // �˵�ѡ���±�
    bool exitFlag = false;                     // �˳���־��Ϊ���ʾ�˳�
    chbrotree *mychbrotree = NULL;

    /**
     * @description: У׼countFile and path
     */
    _getcwd(path, MAX_FILE_NAME); // ��ȡ��ǰ����·��
    printf("_getcwd: %s\n", path);
    strcat(path, "\\*.dat");
    int countFile = ls(path);

    char fileName[MAX_STRING];
    char firstName[MAX_STRING];
    char secondName[MAX_STRING];
    info myinfo;
    char relation[MAX_STRING];
    char relationName[MAX_STRING];
    int IdFind;
    int generation;
    char direction[MAX_STRING];
    bool fileOpenFlag = false;

    printf("Input \"help\" for more.\n");
    while (true)
    {
        PRINT_FONT_GRE
        // if (mychbrotree)
        if (fileOpenFlag)
        {
            printf("dev\\%s> ", inputFileName);
        }
        else
        {
            printf("dev> ");
        }
        PRINT_ATTR_REC

        // ����������ļ�ֵ
        scanf("%s", strSel);
        // add del and clear
        for (indexSel = 0; indexSel < MENU_SEL; indexSel++)
        {
            if (!strcmp(strSel, menuSel[indexSel]))
            {
                break;
            }
        }
        switch (indexSel)
        {
        case MENU_PRINT:
            menuPrint();
            break;
        case LS:
            // ls
            printf("There are %d files in total\n", countFile);
            for (int i = 0; i < countFile; i++)
            {
                printf("%s\n", searchFileName[i]);
            }
            break;
        case MK:
            // mk
            scanf("%s", fileName);
            mk(fileName);
            countFile = ls(path); // У׼countFile and searchFileName
            break;
        case OPEN:
            // open // load
            scanf("%s", inputFileName);
            for (int i = 0; i < countFile; i++)
            {
                if (!strcmp(inputFileName, searchFileName[i]))
                {
                    fileExist = true;
                    if (!strcmp(outputFileName, inputFileName))
                    {
                        printf("file already open\n");
                        break;
                    }
                    // if (mychbrotree != NULL)
                    if (fileOpenFlag)
                    {
                        printf("Saving previous data file to %s...\n", outputFileName);
                        save(mychbrotree, outputFileName);
                        mychbrotree = NULL;
                        printf("Save finished\n");
                    }
                    else
                    {
                        strcpy(outputFileName, inputFileName);
                        printf("Initialize memory, load data to memory\n");
                        mychbrotree = load(mychbrotree, inputFileName);
                        fileOpenFlag = true;
                        printf("Load finished\n");
                    }
                    break;
                }
            }
            if (!fileExist)
            {
                printf("File does not exist\n");
            }
            fileExist = false;
            break;
        case CLOSE:
            // close
            if (fileOpenFlag)
            {
                save(mychbrotree, outputFileName);
                printf("Save finished\n");
                // û���ͷ��ڴ�
                mychbrotree = NULL;
                *outputFileName = '\0';
                fileOpenFlag = false;
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case DEL:
            // del
            scanf("%s", inputFileName);
            if (!remove(inputFileName))
            {
                printf("Delete successful\n");
                countFile = ls(path);
            }
            else
            {
                PRINT_FONT_RED
                fprintf(stderr, "%s\n", strerror(errno));
                PRINT_ATTR_REC
            }
            // ���ɾ�����ļ��͵�ǰ�򿪵��ļ���ͬһ���ļ����ͷ�mychbrotree
            if (!strcmp(inputFileName, outputFileName))
            {
                mychbrotree = delAllTree(mychbrotree);
                fileOpenFlag = false;
            }

            break;
        case CLEAR:
            // clear������ڴ򿪵������ļ�
            if (fileOpenFlag)
            {

                PRINT_FONT_RED
                printf("Empty this file?\n");
                PRINT_ATTR_REC
                printf("continue?(input 'y' or 'Y' to continue)\n");
                char consel[1];
                scanf("%s", consel);
                if (consel[0] == 'Y' || consel[0] == 'y')
                {
                    mychbrotree = delAllTree(mychbrotree);
                    save(mychbrotree, inputFileName);
                    printf("clear successful\n");
                    mychbrotree = load(mychbrotree, inputFileName);
                    printf("Reload finished\n");
                }
                else
                {
                    printf("operation aborted\n");
                }
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case ID_FIND_PERSON:
            if (fileOpenFlag)
            {
                scanf("%d", &IdFind);
                idFindPerson(mychbrotree, IdFind);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case NAME_FIND_PERSON:
            if (fileOpenFlag)
            {
                scanf("%s", firstName);
                if (!nameFindPerson(mychbrotree, firstName, MAX_FIND_DEEPTH))
                {
                    PRINT_FONT_RED
                    printf("Not fount\n");
                    PRINT_ATTR_REC
                }
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case MODIFY:
            if (fileOpenFlag)
            {
                scanf("%s", firstName);
                mychbrotree = modify(mychbrotree, firstName);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case INPUT:
            // input
            if (fileOpenFlag)
            {
                scanf("%s%s", relation, relationName);
                scanf("%s%s%s%s", myinfo.name, myinfo.sex, myinfo.birth, myinfo.spouse);
                mychbrotree = treeInput(mychbrotree, myinfo, relation, relationName);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case PRINT_TREE_NODE:
            if (fileOpenFlag)
            {
                printTreeNode(mychbrotree);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case GENERAT:
            if (fileOpenFlag)
            {
                // ���²���ֻ�����²���1���� ���ϲ��ҿ��Բ��Ҹ�ϵgeneration��
                scanf("%s%s", firstName, direction);
                if (!strcmp(direction, "before"))
                {
                    scanf("%d", &generation);
                }
                else if (!strcmp(direction, "after"))
                {
                    generation = 1;
                }
                printCondition(mychbrotree, firstName, direction, generation);
            }
            else
            {
                PRINT_FONT_RED
                printf("Not save, retry\n");
                PRINT_ATTR_REC
            }
            break;
        case FIND_RELATION:
            scanf("%s%s", firstName, secondName);
            chbrotree *firstPerson = nameFindPerson(mychbrotree, firstName, MAX_FIND_DEEPTH);
            chbrotree *secondPerson = nameFindPerson(mychbrotree, secondName, MAX_FIND_DEEPTH);
            transToAppellation(mychbrotree, firstPerson, secondPerson);
            break;
        case EXIT:
            exitFlag = true;
            // �����ļ�
            if (fileOpenFlag)
            {
                if (save(mychbrotree, outputFileName))
                {
                    printf("Save finished\n");
                    // �ͷ��ڴ�
                    mychbrotree = delAllTree(mychbrotree);
                    mychbrotree = NULL;
                    fileOpenFlag = false;
                }
                else
                {
                    PRINT_FONT_RED
                    printf("Not save, retry\n");
                    PRINT_ATTR_REC
                }
            }
            break;
        default:
            printf("'%s' is not an internal command\n", strSel);
            break;
        }
        // printf("Execution completed\n");
        if (exitFlag)
        {
            break;
        }
    }
    // system("pause");
    return 0;
}

/**
 * @description: menuPrint
 * @author: LiuKai
 * @param: void
 * @return: void
 * @ver: 2.0 2019/12/21
 */
void menuPrint()
{
    printf("help             format: help\n"
           "ls               format: ls\n"
           "mk               format: mk [*.dat]\n"
           "open             format: open [*.dat]\n"
           "save and close   format: close\n"
           "load             format: laod [*.dat]\n"
           "del              format: del [*.dat]\n"
           "clear all date   format: clear\n"
           "idFindPerson     format: idFindPerson [id]\n"
           "nameFindPerson   format: nameFindPerson [name]\n"
           "modify           format: modify [searchName]\n"
           "treeInput        format: input [relation][relationName][name][sex][birth][spouse]\n"
           "printTreeNode    format: printTree\n"
           "printGenerat     format: printGenert [name][after] or printGenert [name][before][generat]\n"
           "findRelation     format: findRelation [name1][name2]\n"
           "exit             format: exit\n");
}

/**
 * @description: ��pathĿ¼�²���.dat�ļ�
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
int ls(char *path)
{
    long hFile = 0;
    struct _finddata_t fileInfo;
    int count = 0;
    if ((hFile = _findfirst(path, &fileInfo)) == -1)
    {
        return 0;
    }
    do
    {
        strcpy(searchFileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // �ж��ļ����������ļ��л����ļ�
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}

/**
 * @description: mk
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
void mk(char *inputFileName)
{
    FILE *pFile;

    pFile = fopen(inputFileName, "wb"); // ����ʹ��txt�ļ�
    if (!pFile)
    {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(pFile);
}
// void del();

/**
 * @description: load
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
chbrotree *load(chbrotree *root, char *fileName)
{
    FILE *input;
    input = fopen(fileName, "rb");
    if (!input)
    {
        PRINT_FONT_RED
        fprintf(stderr, "%s\n", strerror(errno));
        PRINT_ATTR_REC
        return NULL;
    }
    chbrotree *p, *pre;
    p = (chbrotree *)malloc(sizeof(chbrotree));
    while (fread(p, sizeof(struct chbrotree0), 1, input))
    {
        root = treeInput(root, p->myinfo, "father", p->myinfo.father);
    }
    fclose(input);
    return root;
}

/**
 * @description: save
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
bool save(chbrotree *root, char *fileName)
{
    FILE *output;
    chbrotree *p, *pre;
    output = fopen(fileName, "wb");
    if (!output)
    {
        PRINT_FONT_RED
        fprintf(stderr, "%s\n", strerror(errno));
        PRINT_ATTR_REC
        return false;
    }
    pre = root;
    while (pre)
    {
        p = pre;
        while (p)
        {
            fwrite(p, sizeof(struct chbrotree0), 1, output);
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    fclose(output);
    return true;
}

/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, int id
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 */
chbrotree *idFindPerson(chbrotree *root, int id)
{
    chbrotree *p, *pre;
    pre = root;
    while (pre)
    {
        p = pre;
        while (p)
        {
            if (p->myinfo.id == id)
            {
                return p;
            }
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    return NULL;
}

/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, char *name, int deepth (deepth������ʾ�������)
 * ���������deepth����ΪMAX_FIND_DEEPTHʱĬ��Ϊ������
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 */
// ������������ż
chbrotree *nameFindPerson(chbrotree *root, char *name, int deepth)
{
    chbrotree *p, *pre;
    chbrotree *address[MAX_STRING];
    pre = root;
    int index = 0;
    while (pre && (deepth--))
    {
        p = pre;
        while (p)
        {
            if (!strcmp(p->myinfo.name, name) || !strcmp(p->myinfo.spouse, name))
            {
                address[index] = p;
                index++;
            }
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    if (index == 1)
    {
        return address[0];
    }
    else if (index > 1)
    {
        // �����������
        printf("+----------+----------+----------+----------+----------+----------+\n"
               "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
               "+----------+----------+----------+----------+----------+----------+\n");
        for (int i = 0; i < index; i++)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", address[i]->myinfo.name, address[i]->myinfo.id, address[i]->myinfo.sex,
                   address[i]->myinfo.birth, address[i]->myinfo.father, address[i]->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
        }
        printf("Input id to find:\n");
        int myIdFind;
        scanf("%d", &myIdFind);
        for (int i = 0; i < index; i++)
        {
            if (address[i]->myinfo.id == myIdFind)
            {
                return p;
            }
        }
    }
    return NULL;
}

chbrotree *modify(chbrotree *root, char *name)
{
    info myinfo;
    printf("enter the name to modify:\n");
    chbrotree *p;
    p = nameFindPerson(root, name, MAX_FIND_DEEPTH);
    if (p == NULL)
    {
        printf("ERROR!This person doesn't exist in the family tree!");
        return NULL;
    }
    else
    {
        printf("Enter the new info:\n");
        scanf("%s%s%s%s%s", p->myinfo.name, p->myinfo.sex,
              p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
        return root;
    }
}

/**
 * @description: addChildToFather
 * @author: LiuXiaoxia
 * @param: chbrotree *Father, chbrotree *Child
 * @return: void
 * @ver: 1.0 2019/12/24
 */
chbrotree *addChildToFather(chbrotree *Father, chbrotree *Child)
{
    strcpy(Child->myinfo.father, Father->myinfo.name);
    Child->myfather = Father;
    chbrotree *next = Father->firstchild;
    Father->firstchild = Child;
    Child->rightsibling = next;
    return Father;
}

/**
 * @description: treeInput ����ڵ���ýڵ�father or mather or others
 * !!!Ů�Ժ������������
 * @author: LiuXiaoxia
 * @param: chbrotree *root, info myinfo, char *relation, char *relationName
 * @return: chbrotree *root
 * @ver: 3.0 2019/12/24
 */
chbrotree *treeInput(chbrotree *root, info myinfo, char *relation, char *relationName)
{
    chbrotree *node;
    node = mallocTreeNode(node, myinfo);

    if (root == NULL)
    {
        strcpy(node->myinfo.father, relationName);
        root = node;
        return root;
    }

    chbrotree *pre = nameFindPerson(root, relationName, MAX_FIND_DEEPTH);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s %s is not exist and modification cannot be saved\n", relation, relationName);
        PRINT_ATTR_REC
        return root;
    }
    if (!strcmp(pre->myinfo.sex, "male"))
    {
        if (!strcmp(relation, "father") || !strcmp(relation, "mother"))
        {

            pre = addChildToFather(pre, node);
        }
        else if (!strcmp(relation, "uncle") || !strcmp(relation, "aunt"))
        {
            chbrotree *newfather = pre->myfather;
            generationPrintTreeNode(newfather->firstchild, 1);
            //�����������Ϣ�ҵ�myinfo�ĸ��׵�ID������
            int myinfoFatherID;
            scanf("%d", &myinfoFatherID);
            chbrotree *p = idFindPerson(newfather->firstchild, myinfoFatherID);
            p = addChildToFather(p, node);
        }
        else if (!strcmp(relation, "grandfather") || !strcmp(relation, "grandmother"))
        {
            generationPrintTreeNode(pre->firstchild, 1);
            //�����������Ϣ�ҵ�myinfo�ĸ��׵�ID������
            int myinfoFatherID;
            scanf("%d", &myinfoFatherID);
            chbrotree *p = idFindPerson(pre->firstchild, myinfoFatherID);
            p = addChildToFather(p, node);
        }
        else if (!strcmp(relation, "son") || !strcmp(relation, "daughter"))
        {
            if (pre->myfather == NULL)
            {
                pre->myfather = node;
                strcpy(node->myinfo.father, "null");
                strcpy(pre->myinfo.father, node->myinfo.name);
                node->firstchild = pre;
                root = node;
            }
            else
            {
                pre = pre->myfather;
                if (pre->myfather == NULL)
                {
                    pre = addChildToFather(pre, node);
                }
            }
        }
        else if (!strcmp(relation, "grandson") || !strcmp(relation, "granddaughter"))
        {
            chbrotree *newfather = pre->myfather->myfather->myfather;
            newfather = addChildToFather(newfather, node);
            node = addChildToFather(node, pre->myfather);
        }
    }
    else
    {
        PRINT_FONT_RED
        printf("Female offspring are not allowed to enter the genealogy\n");
        PRINT_ATTR_REC
    }
    return root;
}

/**
 * @description: �ͷų�ͷ���������нڵ���ڴ�
 * @autor: liuXiaoxia
 * @param {type}
 * @return: head;
 * @ver: 1.0 2019/12/23
 */
chbrotree *delAllTree(chbrotree *root)
{
    if (root)
    {
        delAllTree(root->rightsibling);
        delAllTree(root->firstchild);
        free(root);
    }
    return NULL;
}

/**
 * @description: mallocTreeNode
 * @author: LiuKai
 * @param: chbrotree *root, info myinfo
 * @return: chbrotree *node
 * @ver: 1.0 2019/12/20
 */
chbrotree *mallocTreeNode(chbrotree *node, info myinfo)
{
    node = (chbrotree *)malloc(sizeof(chbrotree));
    node->myinfo = myinfo;
    node->firstchild = node->rightsibling = NULL;
    node->myfather = NULL;
    node->myinfo.id = ID;
    ID++;
    return node;
}

/**
 * @description: printTreeNode
 * @author: LiuKai
 * @param: chbrotree *root
 * @return: void
 * @ver: 1.0 2019/12/22
 */
void printTreeNode(chbrotree *root)
{
    int rowTotal = 0;
    /*     if (root == NULL)
    {
        return NULL;
    } */
    // �Ը��ڵ���
    // linkStack mystack;
    /* if (colorCount == 0)
    {
        PRINT_FONT_RED
    }
    colorCount ++; */
    // ����������
    /*
    +---------+----------+--------+-------+----------+
    |Name     |ID        |sex     |Birth  |Spouse    |          
    +---------+----------+--------+-------+----------+
    |1        |2         |3       |4      |5         |
    +---------+----------+--------+-------+----------+
    1 rows in table
    */
    /* printf("%s %d %s %s %s\n", root->myinfo.name, root->myinfo.id, root->myinfo.sex, root->myinfo.birth, root->myinfo.spouse);
    printTreeNode(root->rightsibling);
    // PRINT_FONT_RED
    printTreeNode(root->firstchild); */
    // �������Ϊ�ǵݹ���ʽ
    chbrotree *p, *pre;
    clock_t start, end;
    float timing = 0.0;
    pre = root;
    start = clock();
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (pre)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
            rowTotal++;
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    end = clock();
    timing = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%d rows in table <%.2f sec>\n", rowTotal, timing);
}

/**
 * @description: generationPrintTreeNode
 * @author: LiuXiaoxia
 * @param: chbrotree *root, int generation
 * @return: void
 * @ver: 1.0 2019/12/24
 */
void generationPrintTreeNode(chbrotree *root, int generation)
{
    int rowTotal = 0;
    chbrotree *p, *pre;
    pre = root;
    clock_t start, end;
    float timing = 0.0;
    start = clock();
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (generation)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
            rowTotal++;
            p = p->rightsibling;
        }
        pre = pre->firstchild;
        generation--;
    }
    end = clock();
    timing = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%d rows in table <%.2f sec>\n", rowTotal, timing);
}

// add printcondition
/**
 * @description: printCondition
 * @author: LiuXiaoxia
 * @param: chbrotree *root, int generation
 * @return: void
 * @ver: 1.0 2019/12/24
 */
void printCondition(chbrotree *root, char *name, char *direction, int generation)
{
    int i = 0;
    generation++;
    bool moveDown = true;
    chbrotree *pre = nameFindPerson(root, name, MAX_FIND_DEEPTH);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s is not exist and modification cannot be saved\n", name);
        PRINT_ATTR_REC
    }
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (generation && pre != NULL)
    {
        printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", pre->myinfo.name, pre->myinfo.id, pre->myinfo.sex,
               pre->myinfo.birth, pre->myinfo.father, pre->myinfo.spouse);
        printf("+----------+----------+----------+----------+----------+----------+\n");
        if (!strcmp("after", direction))
        {
            if (moveDown)
                pre = pre->firstchild;
            moveDown = false;
            pre = pre->rightsibling;
        }
        else if (!strcmp("before", direction))
        {
            pre = pre->myfather;
            generation--;
        }
    }
}

/*
void isSpouse (char *s, chbrotree *person, char *name)
{
    if (person->myinfo.name == name)
    {
        strcpy(s, person->myinfo.sex);
    }
    else
    {
        if (person->myinfo.sex == "female")
        {
            strcpy(s, "male");
        }
        else if (person->myinfo.sex == "male")
        {
            strcpy(s, "female");
        }
    }
}*/

/**
 * @description: conGeneration
 * @author: LiuXiaoxia
 * @param: chbrotree *firstPerson, chbrotree *secondPerson
 * @return: chbrotree *
 * @ver: 1.0 2019/12/25
 */
chbrotree *conGeneration(chbrotree *firstPerson, chbrotree *secondPerson)
{
    chbrotree *p = firstPerson;
    if (p->myfather != NULL)
    {
        p = p->myfather;
        if (p->firstchild != NULL)
        {
            p = p->firstchild;
        }
    }
    while (p)
    {
        if (p->myinfo.name == secondPerson->myinfo.name || p->myinfo.spouse == secondPerson->myinfo.name)
        {
            return p;
        }
        p = p->rightsibling;
    }
    return NULL;
}

/**
 * @description: modifyRelation
 * @author: LiuXiaoxia
 * @param: chbrotree *p, int *idx, chbrotree *pSpouse, chbrotree *secondPerson
 * @return: bool
 * @ver: 1.0 2019/12/25
 */
bool modifyRelation(chbrotree *p, int *idx, chbrotree *pSpouse, chbrotree *secondPerson)
{
    // int id = *idx;
    if (p->myinfo.sex == "male")
    {
        rela[*idx].relation = 's';
        strcpy(rela[(*idx)++].name, p->myinfo.name);
    }
    else
    {
        rela[*idx].relation = 'd';
        strcpy(rela[(*idx)++].name, p->myinfo.name);
    }

    if (pSpouse)
    {
        if (pSpouse->myinfo.sex != secondPerson->myinfo.sex)
        {
            rela[*idx].relation = 'p'; //pΪ��ż
            strcpy(rela[(*idx)++].name, pSpouse->myinfo.name);
        }
        return true;
    }
    return false;
}

/**
 * @description: difGeneration
 * @author: LiuXiaoxia
 * @param: chbrotree *root, char *firstName, char *secondName
 * @return: int
 * @ver: 1.0 2019/12/25
 */
int difGeneration(chbrotree *root, chbrotree *firstPerson, chbrotree *secondPerson)
{
    // chbrotree *firstPerson = nameFindPerson(root, firstName, MAX_FIND_DEEPTH);
    // chbrotree *secondPerson = nameFindPerson(root, secondName, MAX_FIND_DEEPTH);
    //char firstSex[100], secondSex[100];
    //isSpouse(firstSex, firstPerson, firstName);
    //isSpouse(secondSex, secondPerson, secondName);

    int idx = 0;
    chbrotree *p, *pre;
    bool flag = false;
    int frequency = 2;
    while (frequency--)
    {
        if (firstPerson->myfather != NULL)
        {
            firstPerson = firstPerson->myfather;
            rela[idx].relation = 'f';
            strcpy(rela[idx++].name, firstPerson->myinfo.name);
        }
    }

    chbrotree *grandfather = firstPerson;
    while (grandfather)
    {
        p = conGeneration(grandfather, secondPerson);
        if (p)
        {
            if (p->myinfo.sex != secondPerson->myinfo.sex)
            {
                rela[idx].relation = 'p';
                strcpy(rela[idx++].name, p->myinfo.name);
            }
            break;
        }

        chbrotree *father = grandfather->firstchild;
        while (father)
        {
            p = conGeneration(father, secondPerson);
            flag = modifyRelation(father, &idx, p, secondPerson);
            if (flag)
                break;

            chbrotree *brother = father->firstchild;
            while (brother)
            {
                p = conGeneration(brother, secondPerson);
                flag = modifyRelation(brother, &idx, p, secondPerson);
                if (flag)
                    break;

                chbrotree *son = brother->firstchild;
                while (son)
                {
                    p = conGeneration(son, secondPerson);
                    flag = modifyRelation(son, &idx, p, secondPerson);
                    if (flag)
                        break;

                    chbrotree *grandson = son->firstchild;
                    while (grandson)
                    {
                        p = conGeneration(grandson, secondPerson);
                        flag = modifyRelation(grandson, &idx, p, secondPerson);
                        if (flag)
                            break;
                        grandson = grandson->rightsibling;
                    }
                    if (flag)
                        break;
                    idx -= 2;
                    son = son->rightsibling;
                }
                if (flag)
                    break;
                idx -= 2;
                brother = brother->rightsibling;
            }
            if (flag)
                break;
            idx -= 2;
            father = father->rightsibling;
        }
        if (flag)
            break;
        idx -= 2;
        break;
    }
    // testProject
    for (int i = 0; i < idx; i++)
    {
        printf("%c", rela[i].relation);
    }
    printf("\n");

    return idx;
}

/**
 * @description: transToAppellation
 * @author: LiuXiaoxia
 * @param: chbrotree *root, chbrotree *firstPerson, chbrotree *secondPerson
 * @return: void
 * @ver: 1.0 2019/12/26
 */
void transToAppellation(chbrotree *root, chbrotree *firstPerson, chbrotree *secondPerson)
{
    int idx = difGeneration(root, firstPerson, secondPerson);
    char appellation[MAX_FIND_DEEPTH][MAX_STRING];
    char prefix[MAX_STRING]; //ǰ׺
    int indexRel = 0;        // relaStr�±�
    int indexAppe = 0;       // ��ά�±�
    int top = 0;             // ջ��
    Relation relaStack[200];

    printf("%s is %s's ", firstPerson->myinfo.name, secondPerson->myinfo.name);
    for (; indexRel < idx; indexRel++)
    {
        strcpy(relaStack[top].name, rela[indexRel].name);
        relaStack[top++].relation = rela[indexRel].relation;
        if (top >= 3 && !strcmp(relaStack[top].name, relaStack[top - 3].name))
        {
            top -= 2;
        }
        // relaStack[indexRel]  = rela[indexRel];
    }

    int i = 0;
    switch (relaStack[i++].relation)
    {
    case '\0': //relaStackΪ��
        printf("self.\n");
        break;
    case 'p': //p
        if (firstPerson->myinfo.sex == "male")
            printf("wife.\n");
        else
            printf("husband.\n");
        break;
    case 's': //s
        switch (relaStack[i++].relation)
        {
        case '\0':
            printf("son.\n");
            break;
        case 'p': //sp
            printf("son's wife.\n");
            break;
        case 's': //ss
            switch (relaStack[i++].relation)
            {
            case '\0':
                printf("grandson.\n");
                break;
            case 'p': //ssp
                printf("grandson's wife.\n");
                break;
            default:
                printf("distant relatives(Blood relationship is too far to query).\n");
                break;
            }
            break;
        case 'd': //sd
            switch (relaStack[i++].relation)
            {
            case '\0':
                printf("grandaughter.\n");
                break;
            case 'p': //sdp
                printf("grandaughter's husband.\n");
                break;
            default:
                printf("distant relatives(Blood relationship is too far to query).\n");
                break;
            }
            break;
        default:
            printf("distant relatives(Blood relationship is too far to query).\n");
            break;
        }
        break;
    case 'd': //d
        switch (relaStack[i++].relation)
        {
        case '\0':
            printf("daughter.\n");
            break;
        case 'p': //dp
            printf("daughter's husband.\n");
            break;
        default:
            printf("distant relatives(Blood relationship is too far to query).\n");
            break;
        }
        break;
    case 'f': //f
        switch (relaStack[i++].relation)
        {
        case '\0':
            printf("father.\n");
            break;
        case 'p': //fp
            printf("mother.\n");
            break;
        case 's': //fs
            switch (relaStack[i++].relation)
            {
            case '\0':
                printf("brother.\n");
                break;
            case 'p':
                printf("brother's wife.\n");
                break;
            case 's': //fss
                switch (relaStack[i++].relation)
                {
                case '\0':
                    printf("nepew.\n");
                    break;
                case 'p': //fssp
                    printf("nepew's wife.\n");
                    break;
                case 's': //fsss
                    switch (relaStack[i++].relation)
                    {
                    case '\0':
                        printf("nepew's son.\n");
                        break;
                    case 'p': //fsssp
                        printf("nepew's son's wife.\n");
                        break;
                    default:
                        printf("distant relatives(Blood relationship is too far to query).\n");
                        break;
                    }
                    break;
                case 'd': //fssd
                    switch (relaStack[i++].relation)
                    {
                    case '\0':
                        printf("nepew's daughter.\n");
                        break;
                    case 'p': //fssdp
                        printf("nepew's daughter's husband.\n");
                        break;
                    default:
                        printf("distant relatives(Blood relationship is too far to query).\n");
                        break;
                    }
                    break;
                default:
                    printf("distant relatives(Blood relationship is too far to query).\n");
                    break;
                }
                break;
            case 'd': //fsd
                switch (relaStack[i++].relation)
                {
                case '\0':
                    printf("niece.\n");
                    break;
                case 'p': //fsdp
                    printf("niece's husband.\n");
                    break;
                default:
                    printf("distant relatives(Blood relationship is too far to query).\n");
                    break;
                }
                break;
            default:
                printf("distant relatives(Blood relationship is too far to query).\n");
                break;
            }
            break;
        case 'd': //fd
            switch (relaStack[i++].relation)
            {
            case '\0':
                printf("sister.\n");
                break;
            case 'p': //fdp
                printf("sister's husband.\n");
                break;
            }
            break;
        case 'f': //ff
            switch (relaStack[i++].relation)
            {
            case '\0':
                printf("grandfather.\n");
                break;
            case 'p': //ffp
                printf("grandmother.\n");
                break;
            case 's': //ffs
                switch (relaStack[i++].relation)
                {
                case '\0':
                    printf("uncle.\n");
                    break;
                case 'p': //ffsp
                    printf("aunt.\n");
                    break;
                case 's': //ffss
                    switch (relaStack[i++].relation)
                    {
                    case '\0':
                        printf("cousin.\n");
                        break;
                    case 'p': //ffssp
                        printf("sister-in-law.\n");
                        break;
                    case 's': //ffsss
                        switch (relaStack[i++].relation)
                        {
                        case '\0':
                            printf("nepew.\n");
                            break;
                        case 'p': //ffsssp
                            printf("nepew's wife.\n");
                            break;
                        case 's': //ffssss
                            switch (relaStack[i++].relation)
                            {
                            case '\0':
                                printf("nepew's son.\n");
                                break;
                            case 'p': //ffssssp
                                printf("nepew's son's wife.\n");
                                break;
                            default:
                                printf("distant relatives(Blood relationship is too far to query).\n");
                                break;
                            }
                            break;
                        case 'd': //ffsssd
                            switch (relaStack[i++].relation)
                            {
                            case '\0':
                                printf("nepew's daughter.\n");
                                break;
                            case 'p': //ffsssdp
                                printf("nepew's daughter's husband.\n");
                                break;
                            default:
                                printf("distant relatives(Blood relationship is too far to query).\n");
                                break;
                            }
                            break;
                        default:
                            printf("distant relatives(Blood relationship is too far to query).\n");
                            break;
                        }
                        break;
                    case 'd': //ffssd
                        switch (relaStack[i++].relation)
                        {
                        case '\0':
                            printf("niece.\n");
                            break;
                        case 'p': //ffssdp
                            printf("niece's husband.\n");
                            break;
                        default:
                            printf("distant relatives(Blood relationship is too far to query).\n");
                            break;
                        }
                        break;
                    default:
                        printf("distant relatives(Blood relationship is too far to query).\n");
                        break;
                    }
                    break;
                case 'd': //ffsd
                    switch (relaStack[i++].relation)
                    {
                    case '\0':
                        printf("cousin.\n");
                        break;
                    case 'p': //ffsdp
                        printf("brother-in-law.\n");
                        break;
                    default:
                        printf("distant relatives(Blood relationship is too far to query).\n");
                        break;
                    }
                    break;
                }
                break;
            case 'd': //ffd
                switch (relaStack[i++].relation)
                {
                case '\0':
                    printf("aunt.\n");
                    break;
                case 'p': //ffdp
                    printf("uncle.\n");
                    break;
                default:
                    printf("distant relatives(Blood relationship is too far to query).\n");
                    break;
                }
                break;
            }
            break;
        default:
            printf("distant relatives(Blood relationship is too far to query).\n");
            break;
        }
        break;
    default:
        printf("distant relatives(Blood relationship is too far to query).\n");
        break;
    }
    return;
}