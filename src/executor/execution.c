/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:03:36 by kyang             #+#    #+#             */
/*   Updated: 2025/02/13 13:02:13 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute(t_ast_node *node, t_shell *shell)
// {
// 	if (node->node_type == COMMAND_SIMPLE)
// 		ft_printf("execute cmd: %s\n", node->value[0]); //execute_commad(node, shell);
// 	else if (node->node_type == COMMAND_PIPE)
// 		ft_printf("%d | %d\n", node->left->node_type, node->right->node_type); //execute_pipe(node->left, node->right, shell);
// 	else if (node->node_type == COMMAND_AND)
// 	{
// 		ft_printf("&&: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
// 		if (shell->status == 0)
// 			ft_printf("&&: r->cmd_type %d\n", node->right->node_type); //executer(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_OR)
// 	{
// 		ft_printf("||: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
// 		if (shell->status == 0)
// 			ft_printf("||: r->cmd: %d\n", node->right->node_type); //executer(node->right, shell);
// 	}
// 	else if (node->node_type == COMMAND_SUBSHELL)
// 		ft_printf("SUBSHELL\n"); //excute_subshell(node, shell);
// }

bool	is_absolute_path(char *arg)
{
	if (arg[0] == '/')
		return (true);
	else if (!ft_strncmp(arg, "./", 2))
		return (true);
	return (false);
}

void	child_pipe_redir_cmd(t_ast_node *node, int *pipex)
{
	int	i;
	int	arg_size;

	i = 0;
	arg_size = 0;
	while(node->value[i])
	{
		arg_size = ft_strlen(node->value[i]);
		if(!ft_strncmp(node->value[i], "<", arg_size) && node->value[i + 1])
		{
			if(node->infile_fd > -1)
				close(node->infile_fd);
			node->infile_fd = open(node->value[i + 1], O_RDONLY, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->infile_fd = open("/dev/null", O_RDONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], ">", arg_size) && node->value[i + 1])
		{
			if(node->outfile_fd > -1)
				close(node->outfile_fd);
			node->outfile_fd = open(node->value[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->outfile_fd = open("/dev/null", O_WRONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], ">>", arg_size) && node->value[i + 1])
		{
			if(node->outfile_fd > -1)
				close(node->outfile_fd);
			node->outfile_fd = open(node->value[i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->outfile_fd = open("/dev/null", O_WRONLY);
			}
			i += 2;
		}
		else if(!ft_strncmp(node->value[i], "<<", arg_size))
		{
			if(node->infile_fd > -1)
				close(node->infile_fd);
			node->infile_fd = open("here_doc.txt", O_RDONLY, 0644);
			if(node->infile_fd < 0)
			{
				ft_putstr_fd("Error: Permisson denied", STDERR_FILENO);
				node->infile_fd = open("/dev/null", O_RDONLY);
			}
			i += 2;
		}
		else
		{
			//CMD
		}
	}
	if(node->outfile_fd < 0)
	{
		if(dup2(pipex[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
}

void	child_pipe_redir_operator(t_ast_node *node, int *pipex)
{
	if(dup2(node->outfile_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if(dup2(pipex[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
}

void	parent_process(t_ast_node *node, t_shell *shell, int *pipex)
{

}

void	child_process(t_ast_node *node, t_shell *shell, int *pipex)
{
	if(node->node_type == COMMAND_SIMPLE)
		child_pipe_redir_cmd(node, pipex);
	else
		child_pipe_redir_operator(node, pipex);
	close(pipex[0]);
	close(pipex[1]);
}
void	execute_pipe(t_ast_node *left_node, t_ast_node *right_node, t_shell *shell)
{
	int		pipex[2];
	pid_t	pid;

	if (pipe(pipex) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(left_node, shell, pipex);
	else
		parent_process(right_node, shell, pipex);
}

void	execute(t_ast_node *node, t_shell *shell)
{
	if (node->node_type == COMMAND_SIMPLE)
		ft_printf("execute cmd: %s\n", node->value[0]); //execute_commad(node, shell);
	else if (node->node_type == COMMAND_PIPE)
		execute_pipe(node->left, node->right, shell);
	else if (node->node_type == COMMAND_AND)
	{
		ft_printf("&&: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
		if (shell->status == 0)
			ft_printf("&&: r->cmd_type %d\n", node->right->node_type); //executer(node->right, shell);
	}
	else if (node->node_type == COMMAND_OR)
	{
		ft_printf("||: l->cmd_type: %d\n", node->left->node_type); //execute(node->left, shell);
		if (shell->status == 0)
			ft_printf("||: r->cmd: %d\n", node->right->node_type); //executer(node->right, shell);
	}
	else if (node->node_type == COMMAND_SUBSHELL)
		ft_printf("SUBSHELL\n"); //excute_subshell(node, shell);
}

void	inorder_traversal(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->node_type == COMMAND_SUBSHELL)
		execute(node, shell);
	inorder_traversal(node->left, shell);
	if (node->node_type >= COMMAND_PIPE && node->node_type <= COMMAND_OR)
		execute(node, shell);
	inorder_traversal(node->right, shell);
}

// void	inorder_traversal(t_ast_node *node, t_shell *shell)
// {
// 	if (!node)
// 		return ;
// 	inorder_traversal(node->left, shell);
// 	executer(node, shell);
// 	inorder_traversal(node->right, shell);
// }

// void	execute_simple_cmd(t_shell *shell, t_token *token_lst)
// {
// }


